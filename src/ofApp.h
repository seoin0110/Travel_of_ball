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
	void setup(); //�ʱⰪ�� ����
	void update();
	void draw(); //���� 15���� �Լ��� ȣ���� �׸�.

	void keyPressed(int key); //�����̽� �ٰ� �ԷµǸ� check�� 140�� ��(140�� ���̸�ŭ jump)
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
	void music_play(ofSoundPlayer x); //����� ���� x�� �Ķ���ͷ� ������ �� ������� ����ϴ� �Լ�
	/*�۾�ü ������*/
	ofTrueTypeFont Dynalight30;
	ofTrueTypeFont Dynalight14;
	ofTrueTypeFont RedFont;
	ofTrueTypeFont RedFont2;
	ofTrueTypeFont RedFont3;
	int draw_flag; //������ ���۵Ǹ� 1�� �ٲ�
	int game_start_flag; //������ ���۵Ǹ� 1�� �ٲ�� mario ������ Ʋ�� �� 0���� �ٽ� �ٲ�
	int start_flag = 0; // ������ ���۵Ǹ� 1�� �ٲ�
	int score = 0; //���ݱ����� ����
	int heart = 120; //���� ����
	int tim = 0; //1�����Ӵ� +1��
	int game_over = 0; //���� ����(heart<0)�� �Ǹ� 1�� �ٲ�
	int moment = 3; //tim�� 15�� �� ������ +1��(1�ʸ� ǥ��)
	int finish_obstacle = 0; //ob�� ���������� ���̴� ��ֹ��� index
	int fast_flag = 0; //heart�� 30���� ������ ����
	int game_over_music = 1; //game_over�� 1�� �� gameover ������ Ʋ�� �� 0���� �ٽ� �ٲ�
	int rank_count = 0; //rank.txt�� �ִ� rank�� ����
	int speed = 7; //��ֹ��� �ٰ����� �ӵ�
	int moment_c = 3; //��ֹ� �����󵵸� �����ϱ� ���� flag
	int new_flag = 0; //���ο� ��� ���ŵƴ��� ����
	int check = 0; //jump�� ����
	/*����� ������*/
	ofSoundPlayer game;
	ofSoundPlayer mario;
	ofSoundPlayer jump;
	ofSoundPlayer heart_music;
	ofSoundPlayer gameover;
	ofSoundPlayer wrong;
	/*�̹��� ����*/
	ofImage img;
	/*���� ����� ����*/
	ifstream fp_in;
	ofstream fp_out;
	vector<obstacle> ob; //��ֹ� obstacle class�� �̿��� vector
	priority_queue<int>pq; //���� ũ������� �����ϱ� ���� prority_queue
	int ss[3] = { 0,0,0 }; //1,2,3���� ����
};