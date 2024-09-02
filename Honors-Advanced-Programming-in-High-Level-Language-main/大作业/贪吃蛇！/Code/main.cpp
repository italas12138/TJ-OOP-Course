#define _CRT_SECURE_NO_WARNINGS
#include"classes.h"
#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<windows.h>

using namespace std;

int Keyboard_monitor(int time_limit, bool flag) {
    time_t beg = clock(), cur;
    char black[] = "                ";     // Ϊ�����ӵ�β���հף����ڸ������
    INPUT_RECORD inRec = { 0 };                    // ������Ϣ�ṹ�壬��¼������Ϣ
    DWORD res;
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);       // ��ȡ����̨��׼������
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);     // ��ȡ����̨��׼������

    // ��������̨�����������
    SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
    while (1) {
        cur = clock();
        //cout << (cur - beg) * 1.0 / CLOCKS_PER_SEC * 1000 << endl;
        if (flag && (cur - beg) * 1.0 / CLOCKS_PER_SEC * 1000 >= time_limit) break;

        // ��ȡ��ǰ������Ϣ������WaitForSingleObject����ֹ�����������첽������
        if (WaitForSingleObject(hInput, 0) == WAIT_OBJECT_0)
            ReadConsoleInputA(hInput, &inRec, 1, &res);

        // ������ƶ������Ͻǣ��������
        COORD zeroPos = { 0,0 };
        SetConsoleCursorPosition(hOutput, zeroPos);

        if (flag && inRec.EventType == KEY_EVENT) {
            int num = inRec.Event.KeyEvent.uChar.UnicodeChar;
            if (num == 97 || num == 100 || num == 115 || num == 119 || num==27) return num;
        }
        if (flag) continue;
        // �����¼�״̬
        switch (inRec.EventType) {
        case KEY_EVENT:
            // �����¼�
            // dwControlKeyState ���¼���̿��Ƽ�״̬�������Сд�Ƿ�����
            // wVirtualKeyCode wVirtualScanCode �����ռ��̰����Ŀ���ʹ�õ���ϱ���
            return inRec.Event.KeyEvent.uChar.UnicodeChar;
            break;
        }
    }
    return -1;
}
int play(Game& G, Wall& W, Food& F, Snake& S, int mode) {

    int keyy = Keyboard_monitor(0, 0);
    while (keyy != 32) keyy = Keyboard_monitor(0, 0); //���ո�ʼ��Ϸ

    int is_over = 0;
    if (mode == 1) {
        while (is_over == 0) {
            int keyb = Keyboard_monitor(150, 1);
            int dir = S.get_dir();
            if (dir == 0 && keyb == 97)continue;
            if (dir == 1 && keyb == 100)continue;
            if (dir == 2 && keyb == 119)continue;
            if (dir == 3 && keyb == 115)continue;
            switch (keyb) {
            case -1:
                S.move(-1, G);
                break;
            case 97:
                S.move(1, G);
                break;
            case 100:
                S.move(0, G);
                break;
            case 115:
                S.move(2, G);
                break;
            case 119:
                S.move(3, G);
                break;
            case 27:
                return is_over;
                break;
            }
            coor* sh = S.snake_head();
            int type = G.query(sh->x, sh->y);

            if (type == 0) { //�ߵ��հ״������·���
                G.upd_map(sh->x, sh->y, 3);
            }
            else if (type == 1) { //ײ��ǽ����Ϸ����
                is_over = 1;
                //break;
            }
            else if (type == 2) { //�Ե�ʳ����ȼ�1��������5
                //cout << "bread��" << endl;
                F.remove(sh->x, sh->y, G); //��remove�����
                S.recover(G);
                G.upd_map(sh->x, sh->y, 3);
                G.add_score();
            }
            else if (type == 3) { //ײ���Լ�����Ϸ����
                is_over = 2;
            }
            Sleep(50);
        }
        if (is_over == 1) {
            IMAGE pic;
            loadimage(&pic, _T("./image/over1.jpg"), 300, 150);
            putimage(800 + 50, 350, &pic);
            return 1;
        }
        else if (is_over == 2) {
            IMAGE pic;
            loadimage(&pic, _T("./image/over2.jpg"), 300, 150);
            putimage(800 + 50, 350, &pic);
            return 2;
        }
    }
    else if (mode == 2) {
        bool ade = 1;
        while (!G.over() && ade) {
            int keyb = Keyboard_monitor(150, 1);
            int dir = S.get_dir();
            if (dir == 0 && keyb == 97)continue;
            if (dir == 1 && keyb == 100)continue;
            if (dir == 2 && keyb == 119)continue;
            if (dir == 3 && keyb == 115)continue;
            switch (keyb) {
            case -1:
                S.move(-1, G);
                break;
            case 97:
                S.move(1, G);
                break;
            case 100:
                S.move(0, G);
                break;
            case 115:
                S.move(2, G);
                break;
            case 119:
                S.move(3, G);
                break;
            case 27:
                return is_over;
                break;
            }
            coor* sh = S.snake_head();
            int type = G.query(sh->x, sh->y);

            if (type == 0) { //�ߵ��հ״������·���
                G.upd_map(sh->x, sh->y, 3);
            }
            else if (type == 1) { //ײ��ǽ����Ϸ����
                ade = S.reset(G, F, W, 1);//��ԭ�����߱���µ�ǽ�ڣ��ٲ����µ���
                //is_over = 1;
                //break;
            }
            else if (type == 2) { //�Ե�ʳ����ȼ�1��������5
                //cout << "bread��" << endl;
                F.remove(sh->x, sh->y, G); //��remove�����
                S.recover(G);
                G.upd_map(sh->x, sh->y, 3);
                G.add_score();
            }
            else if (type == 3) { //ײ���Լ�����Ϸ����
                ade = S.reset(G, F, W, 1);
                //is_over = 2;
            }
            Sleep(50);
        }
        if (is_over == 1) {
            IMAGE pic;
            loadimage(&pic, _T("./image/over1.jpg"), 300, 150);
            putimage(800 + 50, 350, &pic);
            //return 1;
        }
        else if (is_over == 2) {
            IMAGE pic;
            loadimage(&pic, _T("./image/over2.jpg"), 300, 150);
            putimage(800 + 50, 350, &pic);
           // return 2;
        }
    }
    else if (mode == 3) {
        bool ade = 1;
        while (!G.over() && ade) {
            int keyb = Keyboard_monitor(150, 1);
            int dir = S.get_dir();
            if (dir == 0 && keyb == 97)continue;
            if (dir == 1 && keyb == 100)continue;
            if (dir == 2 && keyb == 119)continue;
            if (dir == 3 && keyb == 115)continue;
            switch (keyb) {
            case -1:
                S.move(-1, G);
                break;
            case 97:
                S.move(1, G);
                break;
            case 100:
                S.move(0, G);
                break;
            case 115:
                S.move(2, G);
                break;
            case 119:
                S.move(3, G);
                break;
            case 27:
                return is_over;
                break;
            }
            coor* sh = S.snake_head();
            int type = G.query(sh->x, sh->y);

            if (type == 0) { //�ߵ��հ״������·���
                G.upd_map(sh->x, sh->y, 3);
            }
            else if (type == 1) { //ײ��ǽ������j--
                ade = S.reset(G, F, W, 2);//��ԭ�����߱���µ�ʳ��ٲ����µ���
                G.die();
                //is_over = 1;
                //break;
            }
            else if (type == 2) { //�Ե�ʳ����ȼ�1��������5
                //cout << "bread��" << endl;
                F.remove(sh->x, sh->y, G); //��remove�����
                S.recover(G);
                G.upd_map(sh->x, sh->y, 3);
                G.add_score();
            }
            else if (type == 3) { //ײ���Լ�������--
                ade = S.reset(G, F, W, 2);
                G.die();
                //is_over = 2;
            }
            Sleep(50);
        }
        is_over = 3;
    }
    return is_over;
}
int main() {
    while (1) {
        srand(time(0));
        int mode = menu();
        while (mode == 0) {
            mode = menu();
        }
        cleardevice();
        if (mode == 4) {

            ifstream fl("./file./record.txt");
            if (!fl.is_open()) {
                cout << "�ļ���ʧ��" << endl;
                exit(1);
            }
            int is_over;
            fl >> is_over;
            if (is_over) {
                fl.close();
                cleardevice();
                IMAGE pic1, pic2, pic3;
                loadimage(&pic1, _T("./image/error.jpg"), 700, 200);
                putimage(250, 120, &pic1);
                loadimage(&pic2, _T("./image/nomore.jpg"), 700, 200);
                putimage(250, 375, &pic2);
                loadimage(&pic3, _T("./image/Esc.jpg"), 700 * 0.86, 200 * 0.86);
                putimage(300, 580, &pic3);
                while (Keyboard_monitor(0, 0) != 27); //��Esc�˳�

            }
            else {
                Game G(fl);
                Food F(fl, G);
                Wall W(fl, G);
                Snake S(fl, G);
                G.show_UI();
                int is_ov = play(G, W, F, S, G.get_mode());
                ofstream fl("./file./record.txt");
                if (!fl.is_open()) {
                    cout << "�ļ���ʧ��" << endl;
                    exit(1);
                }
                fl << is_ov << endl;
                fl.close();
                G.~Game();
                F.~Food();
                W.~Wall();
                S.~Snake();
                while (Keyboard_monitor(0, 0) != 27);
            }
        }
        else {
            Game G(mode);
            Food F(G);
            Wall W(G);
            Snake S(G);
            G.show_UI();
            int is_ov = play(G, W, F, S, mode);
            ofstream fl("./file./record.txt");
            if (!fl.is_open()) {
                cout << "�ļ���ʧ��" << endl;
                exit(1);
            }
            fl << is_ov << endl;
            fl.close();
            G.~Game();
            F.~Food();
            W.~Wall();
            //IMAGE pic1;
            //loadimage(&pic1, _T("./image/error.jpg"), 700, 200);
            //putimage(250, 120, &pic1);
            S.~Snake();
            //Sleep(2000);
            while (Keyboard_monitor(0, 0) != 27);
        }
    }
    return 0;
}
