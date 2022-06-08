#pragma once

#include "ofMain.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <queue>

class obstacle {
public:
	int x;
	int y;
	int heart;
};

class ofApp : public ofBaseApp {

public:
	void setup(); //초기값들 설정
	void update();
	void draw(); //매초 15번씩 함수를 호출해 그림.

	void keyPressed(int key); //스페이스 바가 입력되면 check의 140을 뺌(140의 높이만큼 jump)
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	void processOpenFileSelection(ofFileDialogResult openFileResult);
private:
	void music_play(ofSoundPlayer x); //오디오 변수 x가 파라미터로 들어오면 그 오디오를 재생하는 함수
	/*글씨체 변수들*/
	ofTrueTypeFont Dynalight30;
	ofTrueTypeFont Dynalight14;
	ofTrueTypeFont RedFont;
	ofTrueTypeFont RedFont2;
	ofTrueTypeFont RedFont3;
	int draw_flag; //게임이 시작되면 1로 바뀜
	int game_start_flag; //게임이 시작되면 1로 바뀌어 mario 음악을 틀은 뒤 0으로 다시 바뀜
	int start_flag = 0; // 게임이 시작되면 1로 바뀜
	int score = 0; //지금까지의 점수
	int heart = 120; //남은 생명
	int tim = 0; //1프레임당 +1됨
	int game_over = 0; //게임 오버(heart<0)이 되면 1로 바뀜
	int moment = 3; //tim이 15가 될 때마다 +1됨(1초를 표시)
	int finish_obstacle = 0; //ob의 마지막으로 보이는 장애물의 index
	int fast_flag = 0; //heart가 30보다 작은지 여부
	int game_over_music = 1; //game_over가 1일 때 gameover 음악을 틀은 뒤 0으로 다시 바뀜
	int rank_count = 0; //rank.txt에 있는 rank의 갯수
	int speed = 7; //장애물이 다가오는 속도
	int moment_c = 3; //장애물 생성빈도를 결정하기 위한 flag
	int new_flag = 0; //새로운 기록 갱신됐는지 여부
	int check = 0; //jump할 높이
	/*오디오 변수들*/
	ofSoundPlayer game;
	ofSoundPlayer mario;
	ofSoundPlayer jump;
	ofSoundPlayer heart_music;
	ofSoundPlayer gameover;
	ofSoundPlayer wrong;
	/*이미지 변수*/
	ofImage img;
	/*파일 입출력 변수*/
	ifstream fp_in;
	ofstream fp_out;
	vector<obstacle> ob; //장애물 obstacle class를 이용한 vector
	priority_queue<int>pq; //점수 크기순으로 정렬하기 위한 prority_queue
	int ss[3] = { 0,0,0 }; //1,2,3등의 점수
};