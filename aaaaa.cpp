#include <iostream>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <vector>
#include <sstream>
/*#include <boost/algorithm/string/replace.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/algorithm/string/erase.hpp>*/
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
using namespace std;

inline bool string_startsWith(string& fullString, string const &start) {
    return (0 == fullString.compare(0, start.length(), start));
}

inline bool string_endsWith(string& fullString, string const &ending) {
    return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
}

ma_result result;
ma_engine engine;

int main(int argc, char** argv) {
	ifstream file;
	vector<string> vid;
	size_t c;
	int splitcount = 0;
	size_t lastindex = 0;
	
	result = ma_engine_init(NULL, &engine);
	if (result != MA_SUCCESS) return result;
	ma_sound sound;
	ma_sound_init_from_file(&engine, "sound.mp3", MA_SOUND_FLAG_DECODE | MA_SOUND_FLAG_ASYNC, NULL, NULL, &sound);
	
	file.open("play.txt");
	while (!file.eof()) {
		if (c == vid.size()) {
        	vid.resize(vid.size() + 1);
        }
		char tmp = '\0';
		file.get(tmp);
		if (tmp != '\0') {
			if (tmp == '.') {
				lastindex = 0;
				splitcount = 0;
				vid[c] += ' ';
			} else if (tmp == 'S' || tmp == 'P' || tmp == 'L' || tmp == 'I' || tmp == 'T') {
				if (tmp == 'S') {
					lastindex = vid[c].length();
				}
				splitcount++;
				vid[c] += tmp;
				if (splitcount == 5) {
					vid[c].erase(lastindex, 5);
					vid[c] += '\n';
					c++;
					splitcount = 0;
					lastindex = 0;
				}
			} else {
				splitcount = 0;
				lastindex = 0;
				vid[c] += tmp;
			}
		}
	}
	
	/*stringstream buf;
	buf << file.rdbuf();
	string contents = buf.str();
	boost::replace_all(contents, ".", " ");
	boost::split_regex(vid, contents, boost::regex("SPLIT"));*/
	
	c = 0;
	splitcount = 0;
	
	file.close();
	
	ma_sound_seek_to_pcm_frame(&sound, 0);
    ma_sound_start(&sound);
    ma_sound_set_pitch(&sound, 1);
    
    /*for (size_t i = 0; i < vid.size(); i++) {
        vid[i] += '\n';
        if (string_endsWith(vid[i], "\n\n\n"))
            boost::erase_tail(vid[i], 2);
        else if (string_endsWith(vid[i], "\n\n"))
            boost::erase_tail(vid[i], 1);
        
        if (string_startsWith(vid[i], "\n\n"))
            boost::erase_head(vid[1], 2);
        else if (string_startsWith(vid[i], "\n"))
            boost::erase_head(vid[1], 1);
    }*/
	
	for (size_t i = 0; i < vid.size(); i++) {
		system("clear");
		cout << vid[i];
		usleep(82500);
		// usleep(80000);
	}
	
	ma_engine_uninit(&engine);
}