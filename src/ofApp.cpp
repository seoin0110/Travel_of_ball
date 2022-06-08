#include "ofApp.h"


void ofApp::setup(){
    ofSetFrameRate(15);
    ofBackground(255,255,255);
    ofSetLineWidth(4);
    draw_flag = 0; //draw_flag 0으로 초기화
    start_flag = 0; //start_flag 0으로 초기화
    /*글꼴들 load*/
    Dynalight30.load("Dynalight.ttf", 50, true, true);
    Dynalight30.setLineHeight(34.0f);
    Dynalight30.setLetterSpacing(1.035);
    Dynalight14.load("Dynalight.ttf", 30, true, true);
    Dynalight14.setLineHeight(23.0f);
    Dynalight14.setLetterSpacing(1.035);
    RedFont.load("빨간우체통.ttf", 20, true, true);
    RedFont.setLineHeight(15.0f);
    RedFont.setLetterSpacing(1.1);
    RedFont2.load("빨간우체통.ttf", 40, true, true);
    RedFont2.setLineHeight(15.0f);
    RedFont2.setLetterSpacing(1.1);
    RedFont3.load("빨간우체통.ttf", 50, true, true);
    RedFont3.setLineHeight(15.0f);
    RedFont3.setLetterSpacing(1.1);
    /*이미지 load*/
    img.load("heart2.png");
    /*배경 음악 및 소리 load*/
    heart_music.load("heart.mp3");
    wrong.load("sound_button_wrong.mp3");
    gameover.load("gameover.mp3");
    game.load("game.mp3");
    game.setLoop(true);
    mario.load("mario.mp3");
    mario.setLoop(true);
    jump.load("jump.mp3");
    if (start_flag == 0) { /*시작 전 배경 음악 재생*/
        game.play();
        game_start_flag = 1;
    }
    fp_in.open("rank.txt"); //rank.txt 파일 읽기 용으로 엶
    if (fp_in.is_open()) { //rank.txt를 여는데 성공했다면
        int n;
        fp_in >> rank_count; //rank의 갯수와
        for (int j = 0; j < rank_count; j++) { //rank들을 읽어 pq에 push
            fp_in >> n;
            pq.push(n);
        }
    }
    else { //rank.txt가 존재하지 않는다면
        rank_count = 0; //rank의 갯수를 0으로 설정
    }
    fp_in.close(); //파일 닫기

}

void ofApp::update(){
}

void ofApp::draw(){

    if (!start_flag) { //start_flag가 0이면 메인 화면 draw
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
    /*배경의 위아래에 직사각형 그리기*/
    ofDrawRectangle(0, 0, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
    ofDrawRectangle(0, 728, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
    ofSetLineWidth(5);

    if( draw_flag ){ //draw_flag가 1이라면 게임화면을 draw
        if (moment >= moment_c) //moment_c 초에 한번 씩 장애물을 생성함
        {
            moment = 0;
            ob.resize(ob.size() + 1);
            ob[ob.size() - 1].x = 1024;
            ob[ob.size() - 1].y = 1 + rand() % 438; //rand() 함수를 이용해 랜덤으로 장애물의 통로 위치 결정
            ob[ob.size() - 1].heart = rand() % 10; //rand()함수를 이용해 랜덤으로 하트를 생성
        }
        for (int i = finish_obstacle;i < ob.size(); i++) { //화면에 보이는 장애물들에서 loop
            ofSetColor(102, 178, 255);
            ofDrawRectangle(ob[i].x, 40, 30, ob[i].y); //위의 장애물
            ofDrawRectangle(ob[i].x, ob[i].y + 290, 30,728- (ob[i].y + 290)); //아래 장애물
            if (!ob[i].heart) { //heart가 생성된다면 하트를 장애물 사이에 그림
                ofSetColor(255, 153, 204);
                img.draw(ob[i].x - 10, ob[i].y + 160, 0, 50, 50);
            }
            ob[i].x -= speed; //장애물이 다가오는 속도만큼 장애물의 x값을 빼줌
            if (ob[i].x <= 0) //x값이 0보다 작아지면 화면에서 사라졌다는 뜻이므로 finish_obstacle을 1 더해줌
                finish_obstacle++;
        }
        ofSetColor(242, 150, 97);
        if (check < 0) { //check가 0보다 작으면 20을 더해줌으로써 jump
            check += 20;
            ofDrawCircle(512, check + 710, 20);
        }
        else { //check가 0보다 같거나 크다면 점프를 안해도 되므로 y좌표 유지
            ofDrawCircle(512, check + 710, 20);
        }
        for (int i = finish_obstacle; i < ob.size();i++) { //화면에 보이는 장애물들에서 loop
            if (abs(ob[i].x+15 - 512) <= 25) //장애물과 공사이의 x좌표 차이가 25보다 같거나 작으면
            {
                if (check + 690 < ob[i].y + 40 || check + 730 > ob[i].y + 290) //장애물과 공이 부딪혔을 때
                {
                    wrong.play(); //wrong 음악 재생
                    heart -= 5; //heart는 5 감소
                    break;
                }
                if (!ob[i].heart && abs(check + 710 - (ob[i].y + 185)) <= 25) //하트와 공이 만났을 때
                {
                    heart += 20; //heart는 20 증가
                    heart_music.play(); //heart_music 재생
                    ob[i].heart = 1; //heart = 1로 만들어 하트를 더이상 그리지 않음
                    break;
                }
            }
        }
        /*점수 출력*/
        ofSetColor(0, 0, 0);
        ofPushMatrix();
        string str3 = "score : " + to_string(score);
        ofTranslate(860, 80, 0);
        RedFont.drawString(str3, 0, 0);
        ofPopMatrix();

        
        ofSetColor(255, 150, 244);
        if (fast_flag) //시간이 얼마 안남았을 때 남은 heart를 빨간색으로 바꿔 출력
            ofSetColor(255, 51, 51);
        ofSetLineWidth(1);
        ofDrawRectangle(10, 60, 3*heart, 20);
        ofSetColor(255, 0, 127);
        img.draw(3*heart-5, 55, 0, 30, 30);
        int i;
        tim++; //매 프레임마다 tim++
        if (heart <= 0) //heart가 0보다 같거나 작아지면 heart = 0으로 game_over = 1로 draw_flag = 0으로
        {
            heart = 0;
            game_over = 1;
            draw_flag = 0;
        }
        if (tim == 15) //1초가 지날 때마다 moment++, heart--, score++, tim은 0으로 초기화
        {
            heart--;
            tim = 0;
            score++;
            moment++;
        }
        if (heart <= 30) { //heart가 30이하라면 hurry up!을 출력
            ofSetColor(255, 0, 0);
            ofPushMatrix();
            string str6 = "Hurry up!!";
            ofRectangle bounds = RedFont.getStringBoundingBox(str6, 0, 0);
            ofTranslate(512, 80, 0);
            RedFont.drawString(str6, -bounds.width / 2,0);
            ofPopMatrix();
        }
        if (heart <= 30 && fast_flag == 0) { //heart가 30이하 및 fast_flag가 0일 때  음악과 장애물 생성 및 다가오는 속도가 빨라짐.
            fast_flag = 1;
            mario.setSpeed(1.5);
            speed = 12;
            moment_c = 2;
            
        }
        else if (heart > 30 && fast_flag == 1) {//heart가 30초과 및 fast_flag가 1일 때  음악과 장애물 생성 및 다가오는 속도가 빨라짐.
            fast_flag = 0;
            mario.setSpeed(1.0);
            speed = 7;
            moment_c = 3;
        }
    }
    
    if (game_over) { //game_over가 1이 되면
        mario.stop(); //game 음악을 재생 중지
        
        if (game_over_music) { //game_over_music이 1이면 (game over된 후 한번만 실행 됨)
            pq.push(score); //현재 score을 pq에 push
            int j = 0;
            for (int i = 0; i < 3;i++)
            {
                if (!pq.empty()) //pq가 비어있지 않다면 pq.top()을 ss[i]에 저장하고 pop()
                {
                    ss[i] = pq.top();
                    pq.pop();
                    j++;
                }
            }
            for (int k = 0; k < j;k++) //ss[i]에 있는 걸 다시 pq에 push gka
                pq.push(ss[k]);
            gameover.play();
            fp_out.open("rank.txt"); //rank.txt파일을 쓰기 모드로 엶
            fp_out << pq.size() <<'\n'; //pq.size()를 쓰고
            while (!pq.empty()) { //pq에 있는 내용들을 pop()하면서 rank.txt에 씀
                fp_out << pq.top() << '\n';
                pq.pop();
            }
            fp_out.close();
            ob.clear(); // 동적 할당 해제
            game_over_music = 0; //한번 실행 후 game_over_music 을 0으로 설정
        }
        ofPushMatrix(); //game over 문구 출력
        ofSetColor(255, 0, 0);
        string str4 = "Game_Over !!";
        ofRectangle bounds =  RedFont3.getStringBoundingBox(str4, 0, 0);
        ofTranslate(512, 320, 0);
        ofScale(0.7 + abs(cos(ofGetElapsedTimef())), 0.7 + abs(cos(ofGetElapsedTimef())), 0.5);
        RedFont3.drawString(str4, -bounds.width / 2, bounds.height / 2);
        ofPopMatrix();

        ofSetColor(0);
        ofPushMatrix();
        string str5 = "Ranking"; //Ranking 출력
        bounds = RedFont2.getStringBoundingBox(str5, 0, 0);
        ofTranslate(512, 460, 0);
        RedFont2.drawString(str5, -bounds.width / 2, bounds.height / 2);
        ofPopMatrix();
        for (int j = 0; j < 3; j++) { //ss[0],ss[1],ss[2]를 각각 1st, 2nd, 3rd rank로 출력
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
            if (ss[j] == score && new_flag == 0) //현재 점수가 순위권에 들게 되면 new를 출력
            {
                ofSetColor(255, 0, 0);
                ofPushMatrix();
                string str = "new";
                bounds = RedFont.getStringBoundingBox(str, 0, 0);
                ofTranslate(610, 530 + j*50, 0);
                RedFont.drawString(str, -bounds.width / 2, bounds.height / 2);
                ofPopMatrix();
                new_flag = 1; //new_flag는 1로 설정

            }
            
        }
        new_flag = 0; //new_flag를 0으로 설정
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key) { //처음에 key가 눌리면
        if (game_start_flag) { //game_start_flag가 1이면 (한번만 실행)
            game.stop(); //게임 시작 전 배경 음악이 중단
            music_play(mario); //게임 음악이 재생
            game_start_flag = 0; game_start_flag = 0;
        }
        start_flag = 1; //start_flag와 draw_flag를 1로 설정
        draw_flag = 1;
        draw();

    }
    if (game_over && key){
        draw_flag = 0;
        _Exit(0);
    }
    if (draw_flag && key == ' '){ //스페이스 바를 누르면 점프
        check -= 140; //check가 140만큼 빼짐
        if (check <= -670) //-670보다 작으면 천장이므로 -670에 고정
            check = -670;
        jump.play();//jump할 때의 소리 재생
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