#include<process.h>

#include<string.h>

#include<dos.h>

#include<stdlib.h>

#include<fstream.h>

#include<conio.h>

#include<stdio.h>

#include<ctype.h>

class player {
        int position;
        char rank[20], name[20];
        unsigned int points;
        int nwon, nlost;

        public:
                player() {
                        nwon = nlost = 0;
                        points = 0;
                }
        void showname() {
                cout << name;
        }
        int getpoints() {
                return points;
        }
        void getname() {
                gets(name);
        }
        void renew() {
                nwon = nlost = 0;
                points = 0;
        }
        void won() {
                nwon++;
                points += points * 10;
                assign_rank();
        }
        void lost() {
                nlost++;
                points = points * (0.9);
                assign_rank();
        }
        void assign_rank() {
                if (points > 200)
                        strcpy(rank, "\"LEGENDRARY\"");
                else if (points > 150)
                        strcpy(rank, "\"ELITE\"");
                else if (points > 100)
                        strcpy(rank, "\"MASTER\"");
                else if (points > 50)
                        strcpy(rank, "\"THUG\"");
                else
                        strcpy(rank, "\"NOOBIE\"");
        }
        void showdet() {
                clrscr();
                textcolor(15);
                textbackground(1);
                cout << "\n\n\n\t\t\t\t\" NO GUTS... NO GLORIES ";
                cout << "\n\t\t\t\t\ NO LEGENDS... NO STORIES ";
                cout << "\n\n\n\t\t\tTHE HIGHEST POSITION IN THIS GAME";
                cout << "\t\t\tBELONGS TO... " << rank << name;
                cout << "\t\t\tWITH " << points << " POINTS.\n";
        }
        void draw() {
                points += 10;
        }
};

struct person {
        char name[20];
        char desig[20];
        char descr[80];
};

#define size 4
void top();
void addplayer(player);
void logo();
void displayboard(char board[size][size]);
int validspots(char board[size][size], int moves[size][size], char player);
void cpumove(char board[size][size], int moves[size][size], char player);
int bestmove(char board[size][size], int moves[size][size], char player);
int finalscore(char board[size][size], char player);
void move(char board[size][size], int r, int c, char player);
void passbackground();
int enterpass();
void startgame(player);
void menu();
void animate(char str[80]);
void whotsit();
void credits();
player nk;

void main() {
        char c;
        //  if(!enterpass())
        //  exit(0);

        do {
                clrscr();
                textcolor(15);
                textbackground(1);

                menu();
                char ch;
                cin >> ch;
                switch (ch) {

                case '1':
                        char ch;

                        clrscr();
                        textcolor(15);
                        textbackground(1);
                        cout << "ENTER YOUR NAME";
                        nk.getname();
                        label:
                                startgame(nk);
                        cout << "again?";
                        cin >> ch;
                        if (tolower(ch) == 'y')
                                goto label;
                        break;
                case '2':
                        clrscr();
                        textcolor(15);
                        textbackground(1);
                        whotsit();
                        break;
                case '3':
                        top();
                        break;
                case '4':
                        credits();
                        break;
                case '5':
                        clrscr();
                        textcolor(15);
                        textbackground(1);
                        cout << " THANKYOU FOR PLAYING ";
                        getch();
                        exit(0);
                        break;
                default:
                        cout << "WRONG CHOICE";
                }

                cout << "\n\nback to the main menu?";
                cin >> c;

        } while (tolower(c) == 'y');

        getch();
}

void startgame(player p) {
        char board[size][size], ytemp, ch;
        int moves[size][size];

        int gameno, moveno, novalmoves, cpuscore, playerscore, player, x, y;

        clrscr();
        textcolor(15);
        textbackground(1);

        //logo();
        textcolor(15);
        textbackground(1);

        cout << "\n\n\n\n\n\n\t\t\t";
        cout << " WELCOME TO THE GAME OTHELLO!! \n\n\n";
        cout << "\n\t\t\tYOU WILL BE WHITE - ( O ) " <<
                "\n\t\t\tI WILL BE BLACK - ( @ ) " <<
                "\n\n\n\t\t\tSELECT A SQUARE FOR YOUR MOVE\n\t\t\t BY TYPING THE ROW NO. AND THE" <<
                "\n\t\t\tLENTER OF THE COLUMN WITH A BLANK IN BTW" <<
                "\n\n\n\t\tGOODLUCK!! PRESS ENTER TO START";
        getch();

        clrscr();
        gameno = 0;
        player = ++gameno;
        moveno = 4;

        for (int r = 0; r < size; r++)
                for (int c = 0; c < size; c++)
                        board[r][c] = ' ';
        board[size / 2 - 1][size / 2 - 1] = board[size / 2][size / 2] = 'O';
        board[size / 2 - 1][size / 2] = board[size / 2][size / 2 - 1] = '@';

        do {
                clrscr();
                displayboard(board);
                if (player % 2) {
                        if (validspots(board, moves, 'O')) {
                                while (1) {
                                        cout << "ENTER YOUR MOVE (ROW COLUMN) ";
                                        cin >> x >> ytemp;
                                        y = tolower(ytemp) - 'a';

                                        x--;

                                        if (x >= 0 && y >= 0 && x < size && y < size && moves[x][y]) {
                                                move(board, x, y, 'O');
                                                moveno++;
                                                player++;
                                                break;
                                        } else
                                                cout << "ENTERED MOVE WAS INVALID!\n";
                                }
                        } else if (++novalmoves < 2) {
                                cout << "\nYou have to pass, press return";
                                getch();
                        } else
                                cout << "\nNO VALID MOVES FOR BOTH, GAME OVER!!.\n";
                } else {
                        if (validspots(board, moves, '@')) {
                                novalmoves = 0;
                                cpumove(board, moves, '@');
                                moveno++;
                                player++;
                        } else {
                                if (++novalmoves < 2) {
                                        cout << "I HAVE TO PASS,YOUR TURN";
                                        player++;
                                } else
                                        cout << "\nNeither of us can go, so the game is over.\n";
                        }
                }
        } while (moveno < size * size && novalmoves < 2);

        displayboard(board);

        cpuscore = playerscore = 0;
        for (r = 0; r < size; r++)
                for (c = 0; c < size; c++) {
                        cpuscore += board[r][c] == '@';
                        playerscore += board[r][c] == 'O';
                }
        cout << "\n\n\t\tTHE FINAL SCORE IS:\n";
        cout << "\t\tME: " << cpuscore << "  YOU: " << playerscore;
        (playerscore > cpuscore) ? p.won(): p.lost();
        if (playerscore == cpuscore)
                p.draw();
        getch();
        clrscr();
        logo();

}

void displayboard(char board[][size]) {
        textcolor(15);

        textbackground(1);

        int row, col;
        char collabel = 'a';
        cout << "\n    ";
        for (col = 0; col < size; col++)
                cout << (char)(col + collabel) << "   ";
        cout << "\n";
        for (row = 0; row < size; row++) {
                cout << "  +";
                for (col = 0; col < size; col++)
                        cout << "---+";
                cout << endl;
                cout << row + 1 << " |";

                for (col = 0; col < size; col++)
                        cout << board[row][col] << "  |";
                cout << "\n";
        }

        cout << "  +";
        for (col = 0; col < size; col++)
                cout << "---+";
        cout << "\n\n\nplayer profile: ";
        nk.showname();
        cout << '\n' << '\n';

}

int validspots(char board[][size], int moves[][size], char player) {
        int valmoves = 0;
        char opponent = (player == 'O') ? '@' : 'O';
        for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                        moves[i][j] = 0;

        /* find squares for valid moves
         a valid move will be on a blank square and will enclose
        at least one opponent square between two player squares */
        for (int r = 0; r < size; r++)
                for (int c = 0; c < size; c++) {
                        if (board[r][c] != ' ')
                                continue;
                        for (int rindex = -1; rindex <= 1; rindex++)
                                for (int cindex = -1; cindex <= 1; cindex++) {

                                        if (r + rindex < 0 || r + rindex >= size || c + cindex < 0 || c + cindex >= size || (rindex == 0 && cindex == 0))
                                                continue;
                                        if (board[r + rindex][c + cindex] == opponent) {
                                                int x = r + rindex;
                                                int y = c + cindex;

                                                while (1) {
                                                        x += rindex;
                                                        y += cindex;

                                                        if (x < 0 || x >= size || y < 0 || y >= size)
                                                                break;
                                                        if (board[x][y] == ' ')
                                                                break;
                                                        /*  if the square has a player counter
                                                          then we have a valid move          */
                                                        if (board[x][y] == player) {
                                                                moves[r][c] = 1;
                                                                valmoves++;
                                                                break;
                                                        }
                                                }
                                        }
                                }
                }
        return valmoves;

}
void cpumove(char board[][size], int moves[][size], char player) {
        int brow, bcol, newscore, score, tempmoves[size][size];
        score = 100;
        char opponent, tempboard[size][size];
        opponent = (player == 'O') ? '@' : 'O';

        for (int row = 0; row < size; row++)
                for (int col = 0; col < size; col++) {
                        if (moves[row][col] == 0)
                                continue;
                        for (int i = 0; i < size; i++)
                                for (int j = 0; j < size; j++)
                                        tempboard[i][j] = board[i][j];

                        move(tempboard, row, col, player);
                        validspots(tempboard, tempmoves, opponent);
                        newscore = bestmove(tempboard, tempmoves, opponent);
                        if (newscore < score) {
                                score = newscore;
                                brow = row;
                                bcol = col;
                        }
                }
        move(board, brow, bcol, player);
}

int finalscore(char board[][size], char player) {
        int score = 0;
        char opponent = (player == 'O') ? '@' : 'O';

        for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++) {
                        if (board[i][j] == opponent)
                                score--;
                        if (board[i][j] == player)
                                score++;
                }
        return score;
}

int bestmove(char board[][size], int moves[][size], char player) {
        char opponent = (player == 'O') ? '@' : 'O';
        char checkboard[size][size];
        int score, newscore;
        score = newscore = 0;
        for (int m = 0; m < size; m++)
                for (int n = 0; n < size; n++) {
                        if (!moves[m][n])
                                continue;
                        for (int i = 0; i < size; i++)
                                for (int j = 0; j < size; j++)
                                        checkboard[i][j] = board[i][j];

                        move(checkboard, m, n, player);
                        newscore = finalscore(checkboard, player);

                        if (score < newscore)
                                score = newscore;
                }
        return score;
}

void move(char board[][size], int r, int c, char player) {
        int rindex, cindex, x, y;
        char opponent = (player == 'O') ? '@' : 'O';
        board[r][c] = player;
        for (rindex = -1; rindex <= 1; rindex++)
                for (cindex = -1; cindex <= 1; cindex++) {
                        if (r + rindex < 0 || r + rindex >= size || c + cindex < 0 || c + cindex >= size || (rindex == 0 && cindex == 0))
                                continue;
                        if (board[r + rindex][c + cindex] == opponent) {
                                x = r + rindex;
                                y = c + cindex;
                                while (1) {
                                        x += rindex;
                                        y += cindex;
                                        if (x < 0 || x >= size || y < 0 || y >= size)
                                                break;
                                        if (board[x][y] == ' ')
                                                break;

                                        if (board[x][y] == player) //two ends found
                                        {
                                                x -= rindex;
                                                y -= cindex;
                                                while (board[x][y] == opponent) {
                                                        board[x][y] = player;
                                                        x -= rindex;
                                                        y -= cindex;
                                                }
                                                break;
                                        }
                                }
                        }
                }

}
void passbackground() {
        clrscr();
        textcolor(15);
        textbackground(1);

        gotoxy(26, 9);

        cout << "_____________________________ ";
        gotoxy(26, 10);
        cout << "|                           | ";
        gotoxy(26, 11);
        cout << "|     ENTER THE PASSWORD    | ";
        gotoxy(26, 12);
        cout << "|      _______________      | ";
        gotoxy(26, 13);
        cout << "|_____|               |_____| ";
        gotoxy(26, 14);
        cout << "      |               |       ";
        gotoxy(26, 15);
        cout << "      |_______________|       ";
        gotoxy(35, 14);
}

int enterpass() {
        label: passbackground();

        char pwd[11];
        strcpy(pwd, "           ");
        for (int i = 0; i < 11; i++) {
                pwd[i] = getch();
                cout << '*';
        }
        char loader[6];strcpy(loader, "     ");
        i = 0;
        int j = 0;

        clrscr();
        passbackground();

        gotoxy(40, 19);
        cout << "VERIFYING" << loader;
        while (i < 15) {
                j++;
                if (j % 1997 == 0) {
                        delay(250);
                        passbackground();
                        gotoxy(40, 19);
                        i++;

                        cout << "VERIFYING" << loader;
                        int z = 0;
                        while (z < 6 && loader[z] == '.') {
                                z++;
                        }
                        if (z <= 4)
                                loader[z] = '.';
                        else
                                strcpy(loader, "     ");
                }
        }
        if (strcmpi(pwd, "isitmeagain") == 0) {
                cout << endl << "\t\t\t" << "correct password";
                return 1;
        } else
                cout << "wrong password";
        getch();
        return 0;
}

void logo() {
        clrscr();
        textcolor(15);
        textbackground(1);
        gotoxy(15, 5);
        cout << "";
        cout << "    /0\\ [X-0-X]   |Z  21  5EEEE  I)     I)     /0\\  ";
        gotoxy(15, 6);
        cout << "   0*0*0  \\H/     ||  ||  [      I)     I)    0*0*0 ";
        gotoxy(15, 7);
        cout << "   0*0*0   H      |zzzz1  5ED    I)     I)    0*0*0 ";
        gotoxy(15, 8);
        cout << "   0*0*0   H      ||  ||  [      I)     I)    0*0*0 ";
        gotoxy(15, 9);
        cout << "    \\0/    H      |Z  21  5EEEE  L))))  L))))  \\0/  ";
        cout << "";
        cout << "";
}

void menu() {
        clrscr();
        logo();
        cout << "\n\n\n\n";
        cout << "\t\t\t1.GIVE IT A GO!!\n\n";
        cout << "\t\t\t2.WHOTSIT?\n\n";
        cout << "\t\t\t3.WHO'S ON THE TOP?\n\n";
        cout << "\t\t\t4.CREDITS\n\n";
        cout << "\t\t\t5.GOT 2 GO!?\n\n";
        cout << "ENTER YOUR CHOICE\n\n";
}

void addplayer(player nk) {
        ofstream mf("player1.dat", ios::binary | ios::app);
        if (!mf) {
                cout << "profile creation failed";
        }
        mf.write((char * ) & nk, sizeof(nk));
        mf.close();
}
void top() {
        player top;
        ifstream mf("player1.dat", ios::binary);
        if (!mf) {
                cout << "game source files missing";
                getch();
        } else {
                player p;
                while (mf) {
                        mf.read((char * ) & p, sizeof(p));
                        if (p.getpoints() > top.getpoints()) {
                                top = p;
                        }
                }
                mf.close();

                clrscr();
                textcolor(15);
                textbackground(1);

                top.showdet();
        }

}

void whotsit() {
        ifstream m("help.txt");
        if (!m) {
                cout << "OTHELLO : source files missing";
                getch();
        } else {
                char line[80];
                while (m) {
                        m.getline(line, 80, '@');
                        cout << ' ' << line;
                }
                m.close();
        }
}

void credits() {
        clrscr();
        textcolor(15);
        textbackground(1);
        person p;
        ifstream mf("credits.txt");
        if (!mf) {
                cout << "OTHELLO : source files missing";
                getch();
        } else {
                char line[40];
                while (mf) {
                        mf.getline(line, 40, ',');
                        cout << line;
                }
                mf.close();
        }

}
