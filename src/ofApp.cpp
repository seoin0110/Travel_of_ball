#include "ofApp.h"


void ofApp::setup(){
    ofSetFrameRate(15);
    ofBackground(255,255,255);
    ofSetLineWidth(4);
    draw_flag = 0; //draw_flag 0���� �ʱ�ȭ
    start_flag = 0; //start_flag 0���� �ʱ�ȭ
    /*�۲õ� load*/
    Dynalight30.load("Dynalight.ttf", 50, true, true);
    Dynalight30.setLineHeight(34.0f);
    Dynalight30.setLetterSpacing(1.035);
    Dynalight14.load("Dynalight.ttf", 30, true, true);
    Dynalight14.setLineHeight(23.0f);
    Dynalight14.setLetterSpacing(1.035);
    RedFont.load("������ü��.ttf", 20, true, true);
    RedFont.setLineHeight(15.0f);
    RedFont.setLetterSpacing(1.1);
    RedFont2.load("������ü��.ttf", 40, true, true);
    RedFont2.setLineHeight(15.0f);
    RedFont2.setLetterSpacing(1.1);
    RedFont3.load("������ü��.ttf", 50, true, true);
    RedFont3.setLineHeight(15.0f);
    RedFont3.setLetterSpacing(1.1);
    /*�̹��� load*/
    img.load("heart2.png");
    /*��� ���� �� �Ҹ� load*/
    heart_music.load("heart.mp3");
    wrong.load("sound_button_wrong.mp3");
    gameover.load("gameover.mp3");
    game.load("game.mp3");
    game.setLoop(true);
    mario.load("mario.mp3");
    mario.setLoop(true);
    jump.load("jump.mp3");
    if (start_flag == 0) { /*���� �� ��� ���� ���*/
        game.play();
        game_start_flag = 1;
    }
    fp_in.open("rank.txt"); //rank.txt ���� �б� ������ ��
    if (fp_in.is_open()) { //rank.txt�� ���µ� �����ߴٸ�
        int n;
        fp_in >> rank_count; //rank�� ������
        for (int j = 0; j < rank_count; j++) { //rank���� �о� pq�� push
            fp_in >> n;
            pq.push(n);
        }
    }
    else { //rank.txt�� �������� �ʴ´ٸ�
        rank_count = 0; //rank�� ������ 0���� ����
    }
    fp_in.close(); //���� �ݱ�

}

void ofApp::update(){
}

void ofApp::draw(){

    if (!start_flag) { //start_flag�� 0�̸� ���� ȭ�� draw
        ofSetColor(0, 128, 255);
        ofPushMatrix();
        string str2 = "20201562 Kim Seoin";
        ofRectangle bounds = RedFont.getStringBoundingBox(str2, 0, 0);
        ofTranslate(512,570, 0);
        RedFont.drawString(str2, -bounds.width / 2, bounds.height / 2);
        ofPopMatrix();
        ofPushMatrix();
        string str3 = "<Press any key to start>";
        bounds = RedFont.getStringBoundingBox(str3, 0, 0);
        ofTranslate(512, 600, 0);
        RedFont.drawString(str3, -bounds.width / 2, bounds.height / 2);
        ofPopMatrix();
        ofPushMatrix();
        string str1 = "Travel Of Ball";
        bounds = Dynalight30.getStringBoundingBox(str1, 0, 0);
        ofTranslate(512,340, 0);
        ofScale(0.7 + abs(cos(ofGetElapsedTimef())), 0.7 + abs(cos(ofGetElapsedTimef())), 0.5);
        Dynalight30.drawString(str1, -bounds.width / 2, bounds.height / 2);
        ofPopMatrix();
    }
    ofSetColor(102,178,255);
    /*����� ���Ʒ��� ���簢�� �׸���*/
    ofDrawRectangle(0, 0, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
    ofDrawRectangle(0, 728, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
    ofSetLineWidth(5);

    if( draw_flag ){ //draw_flag�� 1�̶�� ����ȭ���� draw
        if (moment >= moment_c) //moment_c �ʿ� �ѹ� �� ��ֹ��� ������
        {
            moment = 0;
            ob.resize(ob.size() + 1);
            ob[ob.size() - 1].x = 1024;
            ob[ob.size() - 1].y = 1 + rand() % 438; //rand() �Լ��� �̿��� �������� ��ֹ��� ��� ��ġ ����
            ob[ob.size() - 1].heart = rand() % 10; //rand()�Լ��� �̿��� �������� ��Ʈ�� ����
        }
        for (int i = finish_obstacle;i < ob.size(); i++) { //ȭ�鿡 ���̴� ��ֹ��鿡�� loop
            ofSetColor(102, 178, 255);
            ofDrawRectangle(ob[i].x, 40, 30, ob[i].y); //���� ��ֹ�
            ofDrawRectangle(ob[i].x, ob[i].y + 290, 30,728- (ob[i].y + 290)); //�Ʒ� ��ֹ�
            if (!ob[i].heart) { //heart�� �����ȴٸ� ��Ʈ�� ��ֹ� ���̿� �׸�
                ofSetColor(255, 153, 204);
                img.draw(ob[i].x - 10, ob[i].y + 160, 0, 50, 50);
            }
            ob[i].x -= speed; //��ֹ��� �ٰ����� �ӵ���ŭ ��ֹ��� x���� ����
            if (ob[i].x <= 0) //x���� 0���� �۾����� ȭ�鿡�� ������ٴ� ���̹Ƿ� finish_obstacle�� 1 ������
                finish_obstacle++;
        }
        ofSetColor(242, 150, 97);
        if (check < 0) { //check�� 0���� ������ 20�� ���������ν� jump
            check += 20;
            ofDrawCircle(512, check + 710, 20);
        }
        else { //check�� 0���� ���ų� ũ�ٸ� ������ ���ص� �ǹǷ� y��ǥ ����
            ofDrawCircle(512, check + 710, 20);
        }
        for (int i = finish_obstacle; i < ob.size();i++) { //ȭ�鿡 ���̴� ��ֹ��鿡�� loop
            if (abs(ob[i].x+15 - 512) <= 25) //��ֹ��� �������� x��ǥ ���̰� 25���� ���ų� ������
            {
                if (check + 690 < ob[i].y + 40 || check + 730 > ob[i].y + 290) //��ֹ��� ���� �ε����� ��
                {
                    wrong.play(); //wrong ���� ���
                    heart -= 5; //heart�� 5 ����
                    break;
                }
                if (!ob[i].heart && abs(check + 710 - (ob[i].y + 185)) <= 25) //��Ʈ�� ���� ������ ��
                {
                    heart += 20; //heart�� 20 ����
                    heart_music.play(); //heart_music ���
                    ob[i].heart = 1; //heart = 1�� ����� ��Ʈ�� ���̻� �׸��� ����
                    break;
                }
            }
        }
        /*���� ���*/
        ofSetColor(0, 0, 0);
        ofPushMatrix();
        string str3 = "score : " + to_string(score);
        ofTranslate(860, 80, 0);
        RedFont.drawString(str3, 0, 0);
        ofPopMatrix();

        
        ofSetColor(255, 150, 244);
        if (fast_flag) //�ð��� �� �ȳ����� �� ���� heart�� ���������� �ٲ� ���
            ofSetColor(255, 51, 51);
        ofSetLineWidth(1);
        ofDrawRectangle(10, 60, 3*heart, 20);
        ofSetColor(255, 0, 127);
        img.draw(3*heart-5, 55, 0, 30, 30);
        int i;
        tim++; //�� �����Ӹ��� tim++
        if (heart <= 0) //heart�� 0���� ���ų� �۾����� heart = 0���� game_over = 1�� draw_flag = 0����
        {
            heart = 0;
            game_over = 1;
            draw_flag = 0;
        }
        if (tim == 15) //1�ʰ� ���� ������ moment++, heart--, score++, tim�� 0���� �ʱ�ȭ
        {
            heart--;
            tim = 0;
            score++;
            moment++;
        }
        if (heart <= 30) { //heart�� 30���϶�� hurry up!�� ���
            ofSetColor(255, 0, 0);
            ofPushMatrix();
            string str6 = "Hurry up!!";
            ofRectangle bounds = RedFont.getStringBoundingBox(str6, 0, 0);
            ofTranslate(512, 80, 0);
            RedFont.drawString(str6, -bounds.width / 2,0);
            ofPopMatrix();
        }
        if (heart <= 30 && fast_flag == 0) { //heart�� 30���� �� fast_flag�� 0�� ��  ���ǰ� ��ֹ� ���� �� �ٰ����� �ӵ��� ������.
            fast_flag = 1;
            mario.setSpeed(1.5);
            speed = 12;
            moment_c = 2;
            
        }
        else if (heart > 30 && fast_flag == 1) {//heart�� 30�ʰ� �� fast_flag�� 1�� ��  ���ǰ� ��ֹ� ���� �� �ٰ����� �ӵ��� ������.
            fast_flag = 0;
            mario.setSpeed(1.0);
            speed = 7;
            moment_c = 3;
        }
    }
    
    if (game_over) { //game_over�� 1�� �Ǹ�
        mario.stop(); //game ������ ��� ����
        
        if (game_over_music) { //game_over_music�� 1�̸� (game over�� �� �ѹ��� ���� ��)
            pq.push(score); //���� score�� pq�� push
            int j = 0;
            for (int i = 0; i < 3;i++)
            {
                if (!pq.empty()) //pq�� ������� �ʴٸ� pq.top()�� ss[i]�� �����ϰ� pop()
                {
                    ss[i] = pq.top();
                    pq.pop();
                    j++;
                }
            }
            for (int k = 0; k < j;k++) //ss[i]�� �ִ� �� �ٽ� pq�� push gka
                pq.push(ss[k]);
            gameover.play();
            fp_out.open("rank.txt"); //rank.txt������ ���� ���� ��
            fp_out << pq.size() <<'\n'; //pq.size()�� ����
            while (!pq.empty()) { //pq�� �ִ� ������� pop()�ϸ鼭 rank.txt�� ��
                fp_out << pq.top() << '\n';
                pq.pop();
            }
            fp_out.close();
            ob.clear(); // ���� �Ҵ� ����
            game_over_music = 0; //�ѹ� ���� �� game_over_music �� 0���� ����
        }
        ofPushMatrix(); //game over ���� ���
        ofSetColor(255, 0, 0);
        string str4 = "Game_Over !!";
        ofRectangle bounds =  RedFont3.getStringBoundingBox(str4, 0, 0);
        ofTranslate(512, 320, 0);
        ofScale(0.7 + abs(cos(ofGetElapsedTimef())), 0.7 + abs(cos(ofGetElapsedTimef())), 0.5);
        RedFont3.drawString(str4, -bounds.width / 2, bounds.height / 2);
        ofPopMatrix();

        ofSetColor(0);
        ofPushMatrix();
        string str5 = "Ranking"; //Ranking ���
        bounds = RedFont2.getStringBoundingBox(str5, 0, 0);
        ofTranslate(512, 460, 0);
        RedFont2.drawString(str5, -bounds.width / 2, bounds.height / 2);
        ofPopMatrix();
        for (int j = 0; j < 3; j++) { //ss[0],ss[1],ss[2]�� ���� 1st, 2nd, 3rd rank�� ���
            ofSetColor(0);
            ofPushMatrix();
            string str = "";
            if (j == 0) {
                str += "1st : ";
            }
            else if (j == 1) str += "2nd : ";
            else str += "3rd : ";
            str += to_string(ss[j]);
            ofRectangle bounds = RedFont.getStringBoundingBox(str, 0, 0);
            ofTranslate(512, 530 + j*50, 0);
            RedFont.drawString(str, -bounds.width / 2, bounds.height / 2);
            ofPopMatrix();
            if (ss[j] == score && new_flag == 0) //���� ������ �����ǿ� ��� �Ǹ� new�� ���
            {
                ofSetColor(255, 0, 0);
                ofPushMatrix();
                string str = "new";
                bounds = RedFont.getStringBoundingBox(str, 0, 0);
                ofTranslate(610, 530 + j*50, 0);
                RedFont.drawString(str, -bounds.width / 2, bounds.height / 2);
                ofPopMatrix();
                new_flag = 1; //new_flag�� 1�� ����

            }
            
        }
        new_flag = 0; //new_flag�� 0���� ����
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key) { //ó���� key�� ������
        if (game_start_flag) { //game_start_flag�� 1�̸� (�ѹ��� ����)
            game.stop(); //���� ���� �� ��� ������ �ߴ�
            music_play(mario); //���� ������ ���
            game_start_flag = 0; game_start_flag = 0;
        }
        start_flag = 1; //start_flag�� draw_flag�� 1�� ����
        draw_flag = 1;
        draw();

    }
    if (game_over && key){
        draw_flag = 0;
        _Exit(0);
    }
    if (draw_flag && key == ' '){ //�����̽� �ٸ� ������ ����
        check -= 140; //check�� 140��ŭ ����
        if (check <= -670) //-670���� ������ õ���̹Ƿ� -670�� ����
            check = -670;
        jump.play();//jump�� ���� �Ҹ� ���
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){


}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
 
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult) { 
    ;
}

void ofApp::music_play(ofSoundPlayer x) {
    x.play();
}