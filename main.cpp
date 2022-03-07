#include<bits/stdc++.h>
#include<conio.h>
#include<windows.h>
#include<io.h>
using namespace std;
#include"JF.hpp"
#include"password.hpp"

#define MAPX ((classic_mode)?(52):((teacher_mode)?81:0))
#define MAPY ((classic_mode)?(17):((teacher_mode)?17:0))
#define CLEAR system("cls");gotoxy(0,0)
#define PAUSE Sleep(100);press=0;while(press==0) {press=getch();}
#define SC user.str_mem[0]=="Simplified Chinese"
#define EN user.str_mem[0]=="English"
#define CE user.str_mem[0]=="Chinglish"

struct pos;
struct _user;
void regis();
void login();
void whats_new();
void _save();
void gotoxy(int x,int y);
void student_init();
void player_init();
void teacher_init();
void map_init();
void users_init();
void menus_init();
void JC_init();
void game_init();
void _map();
void start_classic();
void start_teacher();
void JC(string s);
void JC_the_teacher();
int mymin(int x,int y);
int do_menu(int id);
void do_bag();
void do_shop();
void getSubdirs(std::string path,vector<string>&files);
void hide_cursor();
void show_cursor();
void color(const unsigned short color1);

int d_x[]={0,0,-1,1};
int d_y[]={-1,1,0,0};
vector<string>users;
vector<string>menu[100];
//bool go_back;
bool classic_mode;
bool teacher_mode;
bool have_JCed_the_teacher=0; 
string jc0,jc1,jc2,jc3,jc4,jc5,jc6,jc7,jc8,jc9,jc10,jc11;
char press=0;
string name_pos[110][110];
vector<string>message; 

struct pos {int x,y;pos(int xx=0,int yy=0) {x=xx;y=yy;}};
struct _user {
	string name;
	string password;
	int ostrakon;
	int int_mem[90];
	string str_mem[10];
	_user(string name2="",string password2="",int ost2=0) {
		name=name2;
		password=password2;
		ostrakon=ost2;
	}
	void update(int memory3[90],string memory4[10]) {
		for(int i=0;i<90;i++) int_mem[i]=memory3[i];
		for(int i=0;i<10;i++) str_mem[i]=memory4[i];
	}
};
_user user;

/*
namespace two_person_mode {
	struct player {
		int a,b,id;
		int count;
		int time;
		player(int a2=4,int y2=2,int id2=1) {
			a=a2;
			b=b2;
			id=id2;
			time=3;
			count=0;
		}
	};
	struct student {
		int id;
		student(int id2=1) {id=id2;}
		void move1() {
			x+=id;
		}
	};
}
*/

class player {
private:
	int count; 
	int x;
	int y;
	bool check(int x,int y) {
		if(y>4&&y<13&&x==50&&mapnow[y][x]=='*') count++;
		else count=0;
		if(count==10) {
			if(user.str_mem[1][1]=='-') {
				user.str_mem[1][1]='+';
				if(EN) {
					message.push_back("Get an achievement!");
					message.push_back("WinterCamping partipactor");
				} else if(SC) {
					message.push_back("获得成就!");
					message.push_back("WC爷");
				} else if(CE) {
					message.push_back("have a done just!");
					message.push_back("WC grandfather");
				}
			}
			count=0;
			return true;
		}
		if(x==0||y==0) return false;
		if(x>=MAPX||y>=MAPY) return false;
		if(mapnow[y][x]!=' ') return false;
		return true;
		count=0;
	}
public:
	bool JCed;
	player(int xx=0,int yy=0) {x=xx;y=yy;}
	int getx() {return x;}
	int gety() {return y;}
	bool check2() {
		if(mapnow[y-1][x]=='+') return true;
		return false;
	}
	bool check3() {
		if(x==24&&y==1) return true;
		return false;
	}
	void print(char c) {
		mapnow[y][x]=c;
		//gotoxy(x,y);
		//cout<<c;
	}
	void move(int d) {
		//cout<<x<<" "<<y<<endl;
		int xx=x+d_x[d];
		int yy=y+d_y[d];
		if(check(xx,yy)) {
			print(' ');
			x=xx;
			y=yy;
			print('x');
		}
	}
	void go_back() {
		print(' ');
		x=44;
		y=15;
		print('x');
	}
};

class teacher {
private:
	int x,y;
	bool go;
	bool back;
	int stay;
	int flag;
	vector<pos>s;
	void print(char c) {
		mapnow[y][x]=c;
	}
public:
	int count;
	teacher(int x2=0,int y2=0) {x=x2,y=y2;s.push_back(pos(x,y));print('O');stay=0;flag=0;}
	void go_back() {
		if(s.size()==1) return;
		if(mapnow[s[s.size()-2].y][s[s.size()-2].x]!='x') {
			print(' ');
			x=s[s.size()-2].x;
			y=s[s.size()-2].y;
			print('O');
			s.pop_back();
		}
	}
	bool on_the_seat() {return (x==s[0].x&&y==s[0].y);}
	bool check() {return 1;}
	bool in_the_classroom() {return (x<=52);}
	void coffee_time() {go=1;flag=0;stay=0;}
	void move() {
		if(stay>0) {
			stay--;
		} else {
			if(go) {
				if(flag==0) {
					if(x==38) {
						flag=1;
						print(' ');
						y++;
						print('O');
						s.push_back(pos(x,y));
					} else {
						print(' ');
						x++;
						print('O');
						s.push_back(pos(x,y));
					}
				} else {
					if(flag==1) {
						flag=2;
						print(' ');
						y++;
						print('O');
						s.push_back(pos(x,y));
					} else {
						if(flag==2) {
							if(x==72) {
								flag=3;
								print(' ');
								y++;
								print('O');
								s.push_back(pos(x,y));
							} else {
								print(' ');
								x++;
								print('O');
								s.push_back(pos(x,y));
							}
						} else {
							if(flag==3) {
								if(y==5) {
									go=0;
									back=1;
									if(user.int_mem[2]==1) {
										stay=90;
									} else if(user.int_mem[1]>0) {
										user.int_mem[1]--;
										stay=90;
									} else stay=30;
								} else {
									print(' ');
									y++;
									print('O');
									s.push_back(pos(x,y));
								}
							}
						}
					}
				}
			} else {
				if(back) {
					if(on_the_seat()) {
						have_JCed_the_teacher=0;
						back=0;
					} else {
						go_back();
					}
				}
			}
		}
	}
};

class student {
private:
	int x,y,id;
	bool gotowc;
	bool backwc;
	int hide;
	string name;
	vector<pos>s;
	//int posmin[20][60]; 
	bool check(int x,int y) {
		if(x==0||y==0) return false;
		if(x>=52||y>=17) return false;
		if(mapnow[y][x]!=' ') return false;
		return true;
	}
	bool check3(int x,int y) {
		return (y>4&&y<14&&x==50);
	}
public:
	int count;
	student(int x2=0,int y2=0,int id2=0,string name2="") {x=x2;y=y2;id=id2;name=name2;hide=0;gotowc=false;}
	
	string getname() {return name;}
	void myinit() {
		s.push_back(pos(x,y));
	}
	void print(char c) {
		mapnow[y][x]=c;
		//gotoxy(x,y);
		//cout<<c;
	}
	void move() {
		if(classic_mode) {
			int d=cyrand(0,3);
			int xx=x+d_x[d];
			int yy=y+d_y[d];
			if(check(xx,yy)) {
				print(' ');
				x=xx;
				y=yy;
				print('o');
				s.push_back(pos(x,y));
				//posmin[y][x]=mymin(posmin[y][x],s.size()-1);
			} else {
				int d=cyrand(0,3);
				int xx=x+d_x[d];
				int yy=y+d_y[d];
				if(check(xx,yy)) {
					print(' ');
					x=xx;
					y=yy;
					print('o');
					s.push_back(pos(x,y));
					//posmin[y][x]=mymin(posmin[y][x],s.size()-1);
				}
			}
		} else {
			if(teacher_mode) {
				if(hide) {
					hide--;
				} else {
					if(gotowc) {
						if(on_the_seat()) {
							int xx=x;
							int yy=y+1;
							if(check(xx,yy)) {
								print(' ');
								x=xx;
								y=yy;
								print('o');
								s.push_back(pos(x,y));
								//posmin[y][x]=mymin(posmin[y][x],s.size()-1);
							}
						} else {
							if(mapnow[y][x+1]!='_'&&mapnow[y][x+1]!='*'&&mapnow[y-1][x]!='*'&&mapnow[y][x+1]!='|'&&mapnow[y-1][x+1]!='_') {
								int xx=x+1;
								int yy=y;
								if(check(xx,yy)) {
									print(' ');
									x=xx;
									y=yy;
									print('o');
									s.push_back(pos(x,y));
									//posmin[y][x]=mymin(posmin[y][x],s.size()-1);
								}
							} else {
								if(mapnow[y][x+1]=='_'||mapnow[y][x+1]=='|'||mapnow[y-1][x+1]=='_') {
									int xx=x;
									int yy=y-1;
									if(check(xx,yy)) {
										print(' ');
										x=xx;
										y=yy;
										print('o');
										s.push_back(pos(x,y));
										//posmin[y][x]=mymin(posmin[y][x],s.size()-1);
									}
								} else {
									//if(mapnow[y][x+1]=='*'||mapnow[y-1][x]=='*') {
									if(check3(x+1,y)||check3(x,y-1)){
										if(user.int_mem[3]==1) hide=90;
										else hide=30;
										print(' ');
										gotowc=0;
										backwc=1;
									}
								}
							}
						}
						
					} else {
						if(backwc) {
							go_back();
							if(x==s[0].x&&y==s[0].y) backwc=false;
						}
					}
				}
			}
		}
	}
		
	void go_back() {
		if(s.size()==1) return;
		if(mapnow[s[s.size()-2].y][s[s.size()-2].x]!='x') {
			print(' ');
			x=s[s.size()-2].x;
			y=s[s.size()-2].y;
			print('o');
			s.pop_back();
		}
	}
	
	void WC() {
		gotowc=1;
	}
	
	bool on_the_seat() {
		return (x==s[0].x&&y==s[0].y);
	}
	
	bool check2() {
		return gotowc||backwc;
	}
};

student st[18];
player jcer;
teacher tc;



int main() {
	system("mode con cols=120 lines=30");
	users_init();
	
	login();
	//user.ostrakon=114514;
	menus_init();
	JC_init(); 
menu1:
	CLEAR;
	int now=do_menu(1);
	int now2;
	int now3;
	char c;
	string passin;
	string newpass;
	switch(now)
	{
	case 1:
menu2:		
		now2=do_menu(2);
		if(now2==1) {
			classic_mode=1;
			start_classic();
			_save();
			classic_mode=0;
			goto menu2;
		} else {
			if(now2==2)  {
				teacher_mode=1;
				start_teacher();
				_save();
				teacher_mode=0;
				goto menu2;
			} else {
				if(now2==3) {
					goto menu1;
				} else {
					goto menu2;
				}
			}
		}
		break;
	case 2:
		do_shop();
		goto menu1;
		break;
	case 3:
		do_bag();
		goto menu1;
		break;
	case 4:
menu4:
		CLEAR;
		now2=do_menu(4);
		switch(now2)
		{
		case 1:
menu5:
			CLEAR;
			now3=do_menu(5);
			switch(now3)
			{
			case 1:
				user.str_mem[0]="Simplified Chinese";
				_save();
				gotoxy(0,0);
				cout<<"设置成功!";
				menus_init();
				JC_init();
				PAUSE;
				goto menu5;
				break;
			case 2:
				user.str_mem[0]="English";
				_save();
				gotoxy(0,0);
				cout<<"Set successfully!";
				menus_init();
				JC_init();
				PAUSE;
				goto menu5;
				break;
			case 3:
				user.str_mem[0]="Chinglish";
				_save();
				gotoxy(0,0);
				cout<<"Set good!";
				menus_init();
				JC_init();
				PAUSE;
				goto menu5;
				break;
			case 4:
				goto menu4;
				break;
			}
			break;
		case 2:
change_the_password:
			CLEAR;
			gotoxy(0,0);
			if(EN) {
				cout<<"Please keyin the password:\n";
			} else if(SC) {
				cout<<"请输入密码:\n";
			} else if(CE) {
				cout<<"Please lost in secret text:\n";
			}
			cin>>passin;
			if(passin==user.password) {
				if(EN) {
					cout<<"Please keyin the new password:\n";
				} else if(SC) {
					cout<<"请输入新密码:\n";
				} else if(CE) {
					cout<<"Please lost in new secret text:\n";
				}
				cin>>newpass;
				user.password=newpass;
				if(EN) {
					cout<<"Set successfully!";
				} else if(SC) {
					cout<<"设置成功!";
				} else if(CE) {
					cout<<"Set good!";
				}
				PAUSE;
				_save();
				goto menu4;
			} else {
				if(EN) {
					cout<<"The password is wrong, please keyin again.";
					PAUSE;
					CLEAR;
					goto change_the_password;
				} else if(SC) {
					cout<<"密码错误,请重新输入.";
					PAUSE;
					CLEAR;
					goto change_the_password;
				} else if(CE) {
					cout<<"Secret test not good, please heavy new lost in.";
					PAUSE;
					CLEAR;
					goto change_the_password;
				}
			}
		case 3:
			goto menu1;
			break;
		}
		break;
	case 5:
		_save();
		exit(0);
		break;
	}
	return 0;
}

void regis() {
_register:
	system("cls");
	string username="";
	cout<<"Please keyin the username:"<<endl;
	cin>>username;
	bool find=0;
	for(int i=0;i<users.size();i++) {
		if(users[i]==username) {
			find=1;
			break;
		}
	}
	if(find) {
		cout<<"The user name already exists. Please change a name and register again.";
		PAUSE;
		system("cls");
		gotoxy(0,0);
		goto _register;
	}
	string password1="";
	cout<<"Please keyin the password:"<<endl;
	cin>>password1;
	string password2="";
	cout<<"Please repeat the password:"<<endl;
	cin>>password2;
	if(password1!=password2) {
		cout<<"The passwords are not the same twice. Please register again.";
		PAUSE;
		system("cls");
		gotoxy(0,0);
		goto _register;
	}
	cout<<"Registered successfully!"<<endl;
	string cmd="mkdir save\\"+username;
	system(cmd.c_str());
	string _path = "save\\"+username+"\\info.txt";
	ofstream fout(_path.c_str());
	fout.close();
	string path="save\\"+username+"\\info.txt";
	freopen(path.c_str(),"w",stdout);
	int key=cyrand(1,100);
	cout<<key<<" ";
	cout<<encry(password1,key)<<" ";
	cout<<encry("0",key)<<" ";
	for(int i=0;i<=79;i++) cout<<encry("0",key)<<" ";
	for(int i=80;i<=98;i++) cout<<encry("NULL",key)<<" ";
	cout<<encry("NULL",key);
	freopen("CON","w",stdout);
	cout<<"Please login again.(Press any key to continue)";
	PAUSE;
	exit(0);
}

void login() {
	char c;
	freopen("CON","r",stdin);
	system("cls");
	gotoxy(0,0);
keyin_username:
	cout<<"Please keyin the username:\n(If not, enter 'register' to register)"<<endl;
	string username="";
	cin>>username;
	if(username=="register") {
		regis();
		return;
	}
	bool find=0;
	for(int i=0;i<users.size();i++) {
		if(users[i]==username) {
			find=1;
			break;
		}
	}
	if(!find) {
		cout<<"This user was not found. Please login again.";
		PAUSE;
		system("cls");
		gotoxy(0,0);
		goto keyin_username;
	}
	
	int key=0;
	string password="";
	string ostrakon_s="";
	int ostrakon=0;
	
	string path="save\\"+username+"\\info.txt";
	char passwordc[10010];
	char ostrakon_sc[10010];
	char memory3_sc[90][10010];
	char memory4c[10][10010];
	string memory3_s[90];
	string memory4[90];
	int memory3[90];
	FILE *fin = NULL;
	fin=fopen(path.c_str(),"rb");
	fscanf(fin,"%d %s %s",&key,&passwordc,&ostrakon_sc);
	for(int i=0;i<90;i++) fscanf(fin,"%s",&memory3_sc[i]);
	for(int i=0;i<10;i++) fscanf(fin,"%s",&memory4c[i]);
	fclose(fin);
	password=passwordc;
	ostrakon_s=ostrakon_sc;
	for(int i=0;i<90;i++) memory3_s[i]=memory3_sc[i];
	for(int i=0;i<10;i++) memory4[i]=memory4c[i];
	
	password=decry(password,key);
	ostrakon_s=decry(ostrakon_s,key);
	
	for(int i=0;i<90;i++) memory3_s[i]=decry(memory3_s[i],key);
	for(int i=0;i<10;i++) memory4[i]=decry(memory4[i],key);
	
	stringstream ss;
	ss<<ostrakon_s;
	ss>>ostrakon;
	for(int i=0;i<90;i++) {
		stringstream ss2;
		ss2<<memory3_s[i];
		ss2>>memory3[i];
	}
	cout<<"Please keyin the password:"<<endl;
	string passin;
	cin>>passin;
	if(passin==password) {
		cout<<"Login successfully! "<<user.str_mem[0];
		user=_user(username,passin,ostrakon);
		if(memory4[1]=="NULL") {
			memory4[1]="";
			for(int i=1;i<=10000;i++) memory4[1]+='-';
		}
		user.update(memory3,memory4);
		PAUSE;
		return;
	} else {
		cout<<"The password is wrong, please log in again.";
		PAUSE;
		CLEAR;
		goto keyin_username;
	}
}

void whats_new() {
	if(EN) {
		gotoxy(50,1);
		cout<<"What's new:";
		gotoxy(50,2);
		cout<<"More merchandises:";
		gotoxy(50,3);
		cout<<"A bag of Cappuccino...";
		gotoxy(50,4);
		cout<<"Add achievements";
		gotoxy(50,5);
		cout<<"Chinglish!";
	} else if(SC) {
		gotoxy(50,1);
		cout<<"更新内容:";
		gotoxy(50,2);
		cout<<"更多商品:";
		gotoxy(50,3);
		cout<<"一包咖啡...";
		gotoxy(50,4);
		cout<<"加入成就";
		gotoxy(50,5);
		cout<<"Chinglish!";
	} else if(CE) {
		gotoxy(50,1);
		cout<<"More new things:";
		gotoxy(50,2);
		cout<<"More many business things:";
		gotoxy(50,3);
		cout<<"one bag Card cloth strange promise...";
		gotoxy(50,4);
		cout<<"Add in done just";
		gotoxy(50,5);
		cout<<"Chinglish!";
	}
}

void _save() {
	CLEAR;
	string path="save\\"+user.name+"\\info.txt";
	FILE *fout = NULL;
	fout=fopen(path.c_str(),"w");
	int key=cyrand(1,100);
	string ostrakon_s;
	stringstream ss;
	ss<<user.ostrakon;   
	ss>>ostrakon_s;
	fprintf(fout,"%d %s %s ",key,encry(user.password,key).c_str(),encry(ostrakon_s,key).c_str());
	for(int i=0;i<=89;i++) {
		stringstream ss2;
		string int_mem_s;
		ss2<<user.int_mem[i];
		ss2>>int_mem_s;
		fprintf(fout,"%s ",encry(int_mem_s,key).c_str());
		//fprintf(fout,"%s ",int_mem_s.c_str());
	}
	for(int i=0;i<=8;i++)
		fprintf(fout,"%s ",encry(user.str_mem[i],key).c_str());
	fprintf(fout,"%s",encry(user.str_mem[9],key).c_str());
	fclose(fout);
	CLEAR;
}

void gotoxy(int x,int y) {CONSOLE_SCREEN_BUFFER_INFO csbiInfo;HANDLE hConsoleOut;hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);csbiInfo.dwCursorPosition.X = x;csbiInfo.dwCursorPosition.Y = y;SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition);}

void student_init() {
	for(int i=1;i<=17;i++) {
		string namenow=names[cyrand(0,(sizeof(names)/sizeof(names[0]))-1)];
		int x=((i-1)%6+1)*8-4;
		int y=7+((i-1)/6)*4;
		st[i]=student(x,y,i,namenow);
		name_pos[y][x]=namenow;
		st[i].myinit();
		/*
		s[i].id=i;
		s[i].x=((i-1)%6+1)*8-4;
		s[i].y=7+((i-1)/6)*4;
		*/
	}
}

void player_init() {
	jcer=player(44,15);
}

void teacher_init() {
	tc.count=0;
	tc=teacher(24,1);
}

void map_init() {
	if(classic_mode) {
		for(int i=0;i<=MAPY-1;i++) {
			mapnow[i]=classic_map[i];
		}
	} else {
		if(teacher_mode) {
			for(int i=0;i<=MAPY-1;i++) {
				mapnow[i]=teacher_map[i];
			}
		}
	}
}

void users_init() {
	getSubdirs("save",users);
}

void menus_init() {
	for(int i=1;i<100;i++) menu[i].clear();
	if(EN) {
		menu[1].push_back("Empty");
		menu[1].push_back("1.Start");
		menu[1].push_back("2.Shop");
		menu[1].push_back("3.Bag");
		menu[1].push_back("4.Setting");
		menu[1].push_back("5.Exit");
		
		menu[2].push_back("Empty");
		menu[2].push_back("1.Classic Mode");
		menu[2].push_back("2.Teacher Mode");
		menu[2].push_back("3.Back");
		
		menu[3].push_back("Empty");
		menu[3].push_back("1.Cappuccino - 20");
		menu[3].push_back("2.A bag of Cappuccino ----------- 80");
		menu[3].push_back("3.A box of Cappuccino ----------- 150");
		menu[3].push_back("4.Coffee maker ------------------ 300");
		menu[3].push_back("5.Toilet seat ------------------- 300");
		menu[3].push_back("6.Back");
		
		menu[4].push_back("Empty");
		menu[4].push_back("1.Language");
		menu[4].push_back("2.Change the password");
		menu[4].push_back("3.Back");
		
		menu[5].push_back("Empty");
		menu[5].push_back("1.简体中文");
		menu[5].push_back("2.English");
		menu[5].push_back("2.Chinglish");
		menu[5].push_back("4.Back");
	} else if(SC) {
		menu[1].push_back("Empty");
		menu[1].push_back("1.开始");
		menu[1].push_back("2.商店");
		menu[1].push_back("3.背包");
		menu[1].push_back("4.设置");
		menu[1].push_back("5.退出");
		
		menu[2].push_back("Empty");
		menu[2].push_back("1.经典模式");
		menu[2].push_back("2.老师模式");
		menu[2].push_back("3.返回");
		
		menu[3].push_back("Empty");
		menu[3].push_back("1.卡布奇诺 ---------------------- 20");
		menu[3].push_back("2.一包咖啡 ---------------------- 80");
		menu[3].push_back("3.一箱咖啡 ---------------------- 150");
		menu[3].push_back("4.咖啡机 ------------------------ 300");
		menu[3].push_back("5.马桶 -------------------------- 200");
		menu[3].push_back("6.返回");
		
		menu[4].push_back("Empty");
		menu[4].push_back("1.语言设置");
		menu[4].push_back("2.更改密码");
		menu[4].push_back("3.返回");
		
		menu[5].push_back("Empty");
		menu[5].push_back("1.简体中文");
		menu[5].push_back("2.English");
		menu[5].push_back("3.Chinglish");
		menu[5].push_back("4.返回");
	} else if(CE) {
		menu[1].push_back("Empty");
		menu[1].push_back("1.Open start");
		menu[1].push_back("2.Business shop");
		menu[1].push_back("3.Back bag");
		menu[1].push_back("4.Set put");
		menu[1].push_back("5.Turn back");
		
		menu[2].push_back("Empty");
		menu[2].push_back("1.Book mod form");
		menu[2].push_back("2.Old teacher mod form");
		menu[2].push_back("3.Turn back");
		
		menu[3].push_back("Empty");
		menu[3].push_back("1.Card cloth strange promise ---- 20");
		menu[3].push_back("2.One bag coffee ---------------- 80");
		menu[3].push_back("3.One box coffee ---------------- 150");
		menu[3].push_back("4.Coffee machine ---------------- 300");
		menu[3].push_back("5.Horse barrel ------------------ 200");
		menu[3].push_back("6.Turn back");
		
		menu[4].push_back("Empty");
		menu[4].push_back("1.Speak set");
		menu[4].push_back("2.Again change secret");
		menu[4].push_back("3.Turn back");
		
		menu[5].push_back("Empty");
		menu[5].push_back("1.简体中文");
		menu[5].push_back("2.English");
		menu[5].push_back("3.Chinglish");
		menu[5].push_back("4.Turn back");
	} else {
		user.str_mem[0]="English";
		
		menus_init();
	}
}

void JC_init() {
#include "init.hpp"
}

void game_init() {
	student_init();
	player_init();
}

void _map() {
	gotoxy(0,0);
	for(int i=0;i<=MAPY-1;i++) {
		cout<<mapnow[i]<<endl;
	}
	if(message.size()>20) {
		while(message.size()==20) message.erase(message.begin());
	}
	for(int i=0;i<message.size();i++) {
		gotoxy(82,i+1);
		cout<<message[i];
	}
}

void start_classic() {
	jcer.JCed=0;
	map_init();
	hide_cursor();
	game_init();
	//int cnt=0;
	while(1) {
		_map();
		for(int i=1;i<=17;i++) {
			if(cyrand(0,99)==0) st[i].move();
		}
		
	    if (!_kbhit()) {
	    	
		} else {
	    	char c=getch();
	    	if(jcer.getx()==44&&jcer.gety()==15&&c=='w') {
				int x=1,y=1;
				system("cls");
				gotoxy(x,y);
				
				cout<<jc10;
				PAUSE;
			} else if(jcer.check2()&&c=='w') {
				JC(name_pos[jcer.gety()][jcer.getx()]);
				jcer.JCed=1;
			} else {
				if(jcer.getx()==50&&c=='d') {
					if(user.str_mem[1][3]=='-') {
						if(EN) {
							message.push_back("Get an achievement!");
							message.push_back("Kind person");
						} else if(SC) {
							message.push_back("获得成就!");
							message.push_back("带善人");
						} else if(CE) {
							message.push_back("Have done just!");
							message.push_back("Carry kind people");
						}
						user.str_mem[1][3]='+';
						_map();
						Sleep(1000);
					}
					break;
				}
			}
	    	switch(c)
	    	{
	    	case 'w':
	    		jcer.move(0);
	    		break;
	    	case 's':
	    		jcer.move(1);
	    		break;
	    	case 'a':
	    		jcer.move(2);
	    		break;
	    	case 'd':
	    		jcer.move(3);
	    		break;
	    	/*
	    	case 'e':
	    		go_back=1;
	    		break;
	    	case 'r':
	    		go_back=0;
	    		break;
	    	*/
			}
		}
	}
	show_cursor();
}

void start_teacher() {
	jcer.JCed=0;
	map_init();
	hide_cursor();
	game_init();
	teacher_init();
	while(1) {
		_map();
		
		for(int i=1;i<=17;i++) {
			if(cyrand(0,9999)==0&&st[i].on_the_seat()) st[i].WC();
		}
		
		for(int i=1;i<=17;i++) {
			
			if(st[i].count>=30) {
				st[i].count=0;
				st[i].move();
			} else {
				if(st[i].check2()) st[i].count++;
			}
			
		}
		
		if(cyrand(0,999)==0&&tc.on_the_seat()) {
			tc.coffee_time();
		}
		
		if(tc.count>=50) {
			tc.count=0;
			tc.move();
		} else tc.count++;
		
		jcer.print('x');
		
		if(
		mapnow[jcer.gety()][jcer.getx()-1]=='o'&&
		mapnow[jcer.gety()][jcer.getx()-2]=='o'&&
		mapnow[jcer.gety()+1][jcer.getx()]=='o'&&
		mapnow[jcer.gety()+2][jcer.getx()]=='o'
		) {
			if(user.str_mem[1][0]=='-') {
				if(EN) {
					message.push_back("Get an achievement!");
					message.push_back("Public indignation");
				} else if(SC){
					message.push_back("获得成就!");
					message.push_back("公愤");
				} else if(CE){
					message.push_back("Have done just!");
					message.push_back("Father angry");
				}
				user.str_mem[1][0]='+';
			}
		}
		
		if(
		mapnow[jcer.gety()][jcer.getx()-1]=='o'&&
		mapnow[jcer.gety()][jcer.getx()+1]=='o'
		) {
			if(user.str_mem[1][2]=='-') {
				if(EN) {
					message.push_back("Get an achievement!");
					message.push_back("Between♂men");
				} else if(SC){
					message.push_back("获得成就!");
					message.push_back("左右♂为男");
				} else if(CE){
					message.push_back("Have done just!");
					message.push_back("Left right♂are men");
				}
				user.str_mem[1][2]='+';
			}
		}
		
	    if (!_kbhit()) {
	    	
		} else {
	    	char c=getch();
	    	if(jcer.getx()==44&&jcer.gety()==15&&c=='w'&&!tc.in_the_classroom()) {
				int x=1,y=1;
				char c=0;
				system("cls");
				gotoxy(x,y);
				cout<<jc10;
				PAUSE;
			} else if(jcer.check2()&&c=='w'&&!tc.in_the_classroom()) {
				JC(name_pos[jcer.gety()][jcer.getx()]);
			} else if(jcer.check3()&&c=='s'&&have_JCed_the_teacher==0) {
				JC_the_teacher();
			}  else {
				if(jcer.getx()==50&&jcer.gety()>13&&c=='d') {
					if(user.str_mem[1][3]=='-') {
						if(EN) {
							message.push_back("Get an achievement!");
							message.push_back("Kind person");
						} else if(SC) {
							message.push_back("获得成就!");
							message.push_back("带善人");
						} else if(SC) {
							message.push_back("Have done just!");
							message.push_back("Carry kind person");
						}
						user.str_mem[1][3]='+';
						_map();
						Sleep(1000);
					}
					break;
				}
			}
	    	switch(c)
	    	{
	    	case 'w':
	    		jcer.move(0);
	    		break;
	    	case 's':
	    		jcer.move(1);
	    		break;
	    	case 'a':
	    		jcer.move(2);
	    		break;
	    	case 'd':
	    		jcer.move(3);
	    		break;
			}
		}
	}
	show_cursor();
}

int time_end;

void update_clock(int beg,int x,int y) {
	gotoxy(x,y-1);
	time_end=clock()-beg;
	if(EN) {
		cout<<"Time : "<<time_end<<"ms";
	} else if(SC) {
		cout<<"用时 : "<<time_end<<"毫秒";
	} else if(CE) {
		cout<<"Use time : "<<time_end<<"Small seconds";
	}
}

void JC(string s) {
	int beg=clock();
	int x=1,y=1;
	char c;
	system("cls");
	gotoxy(x,y);
	cout<<jc0;
	
	while(c!='I') {
		if(!_kbhit()) {
			update_clock(beg,x,y);
		} else c=getch();
	}
	gotoxy(x,y);
	cout<<jc1;
	
	while(c!=' ') {
		if(!_kbhit()) {
			update_clock(beg,x,y);
		} else c=getch();
	}
	gotoxy(x,y);
	cout<<jc2;
	
	while(c!='A') {
		if(!_kbhit()) {
			update_clock(beg,x,y);
		} else c=getch();
	}
	gotoxy(x,y);
	cout<<jc3;
	
	while(c!='K') {
		if(!_kbhit()) {
			update_clock(beg,x,y);
		} else c=getch();
	}
	gotoxy(x,y);
	cout<<jc4;
	
	while(c!=' ') {
		if(!_kbhit()) {
			update_clock(beg,x,y);
		} else c=getch();
	}
	gotoxy(x,y);
	cout<<jc5;
	
	while(c!='I') {
		if(!_kbhit()) {
			update_clock(beg,x,y);
		} else c=getch();
	}
	gotoxy(x,y);
	cout<<jc6;
	
	while(c!='O') {
		if(!_kbhit()) {
			update_clock(beg,x,y);
		} else c=getch();
	}
	gotoxy(x,y);
	cout<<jc7;
	
	while(c!='I') {
		if(!_kbhit()) {
			update_clock(beg,x,y);
		} else c=getch();
	}
	gotoxy(x,y);
	cout<<jc8;
	
	while(c!=13) {
		if(!_kbhit()) {
			update_clock(beg,x,y);
		} else c=getch();
	}
	gotoxy(x,y);
	cout<<jc9;
	
	gotoxy(x+13,y+3);
	cout<<s;
	
	PAUSE;
	user.ostrakon++;
	if(user.int_mem[0]==0) {
		user.int_mem[0]=time_end;
	} else {
		if(time_end<user.int_mem[0]) {
			user.ostrakon+=2;
			user.int_mem[0]=time_end;
		}
	}
}

void JC_the_teacher() {
	have_JCed_the_teacher=true;
	system("cls");
	gotoxy(0,0);
	cout<<jc11;
	gotoxy(1,4);
	int nowx=2,x2=1;
	int nowy=4,y2=0;
	int begin_time=clock();
	gotoxy(nowx,nowy);
	color(6);
	cout<<'o';
	color(7);
	while(clock()-begin_time<=10000) {
		gotoxy(1,2);
		if(EN) {
			cout<<"Time : "<<clock()-begin_time<<"ms";
		} else if(SC) {
			cout<<"用时 : "<<clock()-begin_time<<"毫秒";
		} else if(CE) {
			cout<<"Use time : "<<clock()-begin_time<<"Small seconds";
		}
		gotoxy(nowx,nowy);
		if(!kbhit()) {
			
		} else {
			char c=getch();
			if(c==224) {
				switch(getch()){
			    case 72:
			        if(nowy!=4) {
			        	y2--;
			        	color(7);
						gotoxy(nowx,nowy);
						cout<<'o';
						nowy-=2;
						color(6);
						gotoxy(nowx,nowy);
						cout<<'o';
						color(7);
					}
			        break;
				case 80:
			      	if(nowy!=8) {
			      		y2++;
			        	color(7);
						gotoxy(nowx,nowy);
						cout<<'o';
						nowy+=2;
						color(6);
						gotoxy(nowx,nowy);
						cout<<'o';
						color(7);
					}
			        break;
			    case 75:
			    	if(nowx!=2) {
			    		x2--;
			        	color(7);
						gotoxy(nowx,nowy);
						cout<<'o';
						nowx-=3;
						color(6);
						gotoxy(nowx,nowy);
						cout<<'o';
						color(7);
					}
					break;
			    case 77:
			        if(nowx!=17) {
			        	x2++;
			        	color(7);
						gotoxy(nowx,nowy);
						cout<<'o';
						nowx+=3;
						color(6);
						gotoxy(nowx,nowy);
						cout<<'o';
						color(7);
					}
					break;
			    }
			} else {
				switch(c){
			    case 'w':
			        if(nowy!=4) {
			        	y2--;
			        	color(7);
						gotoxy(nowx,nowy);
						cout<<'o';
						nowy-=2;
						color(6);
						gotoxy(nowx,nowy);
						cout<<'o';
						color(7);
					}
			        break;
				case 's':
			      	if(nowy!=8) {
			      		y2++;
			        	color(7);
						gotoxy(nowx,nowy);
						cout<<'o';
						nowy+=2;
						color(6);
						gotoxy(nowx,nowy);
						cout<<'o';
						color(7);
					}
			        break;
			    case 'a':
			    	if(nowx!=2) {
			    		x2--;
			        	color(7);
						gotoxy(nowx,nowy);
						cout<<'o';
						nowx-=3;
						color(6);
						gotoxy(nowx,nowy);
						cout<<'o';
						color(7);
					}
					break;
			    case 'd':
			        if(nowx!=17) {
			        	x2++;
			        	color(7);
						gotoxy(nowx,nowy);
						cout<<'o';
						nowx+=3;
						color(6);
						gotoxy(nowx,nowy);
						cout<<'o';
						color(7);
					}
					break;
			    case 13:
			    	int JC_begin=clock();
			    	if(y2*6+x2==18) {
			    		CLEAR;
			    		gotoxy(0,0);
			    		cout<<jc10;
			    		PAUSE
					} else JC(st[y2*6+x2].getname());
					int JC_end=clock();
					begin_time+=JC_end-JC_begin;
					CLEAR;
					cout<<jc11;
					gotoxy(nowx,nowy);
					color(6);
					cout<<"o";
					color(7);
			    	break;
			    }
			}
		}
		
	}
}

int mymin(int x,int y) {return x<y?x:y;}

int do_menu(int id) {
	CLEAR;
	if(id==3) {
		gotoxy(0,0);
		if(EN) {
			cout<<"Ostrakon : "<<user.ostrakon;
		} else if(SC) {
			cout<<"陶片 : "<<user.ostrakon;
		} else if(SC) {
			cout<<"Pottery piece : "<<user.ostrakon;
		}
	}
	for(int i=1;i<=menu[id].size()-1;i++) {
		gotoxy(1,i);
		cout<<menu[id][i]<<endl;
	}
	int pr=233,now=1;
	color(6);
	gotoxy(1,now);
	cout<<menu[id][now];
	color(7);
	
	if(id==1) {
		whats_new();
	}
	
	while(pr!=13) {
		pr=getch();
		if(pr==224) {
			switch(getch()){
		        case 72:
		        	color(7);
					gotoxy(1,now);
					cout<<menu[id][now];
					if(now==1) {
						now=menu[id].size()-1;
					} else {
						now--;
					}
					color(6);
					gotoxy(1,now);
					cout<<menu[id][now];
					color(7);
		           break;
		        case 80:
					color(7);
					gotoxy(1,now);
					cout<<menu[id][now];
					if(now==menu[id].size()-1) {
						now=1;
					} else {
						now++;
					}
					color(6);
					gotoxy(1,now);
					cout<<menu[id][now];
					color(7);
		            break; 
		     }
		} else {
			if(pr=='s') {
				color(7);
				gotoxy(1,now);
				cout<<menu[id][now];
				if(now==menu[id].size()-1) {
					now=1;
				} else {
					now++;
				}
				color(6);
				gotoxy(1,now);
				cout<<menu[id][now];
				color(7);
			}
			if(pr=='w') {
				color(7);
				gotoxy(1,now);
				cout<<menu[id][now];
				if(now==1) {
					now=menu[id].size()-1;
				} else {
					now--;
				}
				color(6);
				gotoxy(1,now);
				cout<<menu[id][now];
				color(7);
			}
		}
	}
	return now;
}

void do_bag() {
	CLEAR;
	if(EN) {
		cout<<"My ostrakons : "<<user.ostrakon<<endl;
		cout<<"The fastest JFCA : "<<user.int_mem[0]<<"ms"<<endl;
		cout<<endl;
		if(user.int_mem[2]==1) {
			cout<<"Cappuccino : Infinity"<<endl;
		} else cout<<"Cappuccino : "<<user.int_mem[1]<<endl;
		cout<<endl;
		cout<<"Achievements:"<<endl;
		if(user.str_mem[1][0]=='+') {
			cout<<"Public indignation"<<endl;
			cout<<"Do you think that the toilet is your house?"<<endl<<endl;
		}
		if(user.str_mem[1][1]=='+') {
			cout<<"WinterCamping participator"<<endl;
			cout<<"sto %%% orz"<<endl<<endl;
		}
		if(user.str_mem[1][2]=='+') {
			cout<<"Between♂men"<<endl;
			cout<<"Ah♂"<<endl<<endl;
		}
		if(user.str_mem[1][3]=='+') {
			cout<<"Kind person"<<endl;
			cout<<"Why do you want to JC?"<<endl<<endl;
		}
	} else if(SC) {
		cout<<"我的陶片 : "<<user.ostrakon<<endl;
		cout<<"最快机惨 : "<<user.int_mem[0]<<"毫秒"<<endl;
		cout<<endl;
		if(user.int_mem[2]==1) {
			cout<<"卡布奇诺 : 无限供应";
		} else cout<<"卡布奇诺 : "<<user.int_mem[1]<<endl;
		cout<<endl;
		cout<<"成就:"<<endl;
		if(user.str_mem[1][0]=='+') {
			cout<<"公愤"<<endl;
			cout<<"你以为厕所是你家啊"<<endl<<endl;
		}
		if(user.str_mem[1][1]=='+') {
			cout<<"WC爷"<<endl;
			cout<<"sto %%% orz"<<endl<<endl;
		}
		if(user.str_mem[1][2]=='+') {
			cout<<"左右♂为男"<<endl;
			cout<<"啊♂"<<endl<<endl;
		}
		if(user.str_mem[1][3]=='+') {
			cout<<"带善人"<<endl;
			cout<<"为什么要JC同学呢?";
		}
	} else if(CE) {
		cout<<"Me's pottery piece : "<<user.ostrakon<<endl;
		cout<<"Best fast machine tragic : "<<user.int_mem[0]<<"Small seconds"<<endl;
		cout<<endl;
		if(user.int_mem[2]==1) {
			cout<<"Card cloth strange promise : No restriction give";
		} else cout<<"Card cloth strange promise : "<<user.int_mem[1]<<endl;
		cout<<endl;
		cout<<"Done just:";
		if(user.str_mem[1][0]=='+') {
			cout<<"Father angry"<<endl;
			cout<<"You think toilet is your home"<<endl<<endl;
		}
		if(user.str_mem[1][1]=='+') {
			cout<<"WC grandfather"<<endl;
			cout<<"sto %%% orz"<<endl<<endl;
		}
		if(user.str_mem[1][2]=='+') {
			cout<<"Left right♂is men"<<endl;
			cout<<"Ah♂"<<endl<<endl;
		}
		if(user.str_mem[1][3]=='+') {
			cout<<"Carry kind people"<<endl;
			cout<<"Why want JC same study?";
		}
	}
	PAUSE;
}

void do_shop() {
menu3:
	CLEAR;
	if(EN) {
		cout<<"Ostrakon : "<<user.ostrakon;
	} else if(SC) {
		cout<<"陶片 : "<<user.ostrakon;
	} else if(CE) {
		cout<<"Pottery piece : "<<user.ostrakon;
	}
	int now2=do_menu(3);
	switch(now2)
	{
	case 1:
		if(user.ostrakon>=20) {
			user.int_mem[1]++;
			user.ostrakon-=20;
			CLEAR;
			if(EN) {
				cout<<"Purchase succeeded!(Press any key to continue)";
			} else if(SC) {
				cout<<"购买成功!(按任意键继续)";
			} else if(CE) {
				cout<<"Buy good!(Click any key go on)";
			}
			char c=getch();
			_save();
			goto menu3; 
		} else {
			CLEAR;
			if(EN) {
				cout<<"Your ostrakons isn't enough!";
			} else if(SC) {
				cout<<"你的陶片不够了!";
			} else if(CE) {
				cout<<"Your pottery piece not enough!";
			}
			goto menu3;
		}
		break;
	case 2:
		if(user.ostrakon>=80) {
			user.int_mem[1]+=5;
			user.ostrakon-=80;
			CLEAR;
			if(EN) {
				cout<<"Purchase succeeded!(Press any key to continue)";
			} else if(SC) {
				cout<<"购买成功!(按任意键继续)";
			} else if(CE) {
				cout<<"Buy good!(Click any key go on)";
			}
			char c=getch();
			_save();
			goto menu3; 
		} else {
			CLEAR;
			if(EN) {
				cout<<"Your ostrakons isn't enough!";
			} else if(SC) {
				cout<<"你的陶片不够了!";
			} else if(CE) {
				cout<<"Your pottery piece not enough!";
			}
			goto menu3;
		}
		break;
	case 3:
		if(user.ostrakon>=150) {
			user.int_mem[1]+=10;
			user.ostrakon-=150;
			CLEAR;
			if(EN) {
				cout<<"Purchase succeeded!(Press any key to continue)";
			} else if(SC) {
				cout<<"购买成功!(按任意键继续)";
			} else if(CE) {
				cout<<"Buy good!(Click any key go on)";
			} else if(CE) {
				cout<<"Your pottery piece not enough!";
			}
			char c=getch();
			_save();
			goto menu3; 
		} else {
			CLEAR;
			if(EN) {
				cout<<"Your ostrakons isn't enough!";
			} else if(SC) {
				cout<<"你的陶片不够了!";
			}
			goto menu3;
		}
		break;
	case 4:
		if(user.ostrakon>=200) {
			user.int_mem[2]=1;
			user.ostrakon-=200;
			CLEAR;
			if(EN) {
				cout<<"Purchase succeeded!(Press any key to continue)";
			} else if(SC) {
				cout<<"购买成功!(按任意键继续)";
			} else if(CE) {
				cout<<"Buy good!(Click any key go on)";
			}
			char c=getch();
			_save();
			goto menu3; 
		} else {
			CLEAR;
			if(EN) {
				cout<<"Your ostrakons isn't enough!";
			} else if(SC) {
				cout<<"你的陶片不够了!";
			} else if(CE) {
				cout<<"Your pottery piece not enough!";
			}
			goto menu3;
		}
		break;
	case 5:
		if(user.ostrakon>=100) {
			user.int_mem[3]=1;
			user.ostrakon-=100;
			CLEAR;
			if(EN) {
				cout<<"Purchase succeeded!(Press any key to continue)";
			} else if(SC) {
				cout<<"购买成功!(按任意键继续)";
			} else if(CE) {
				cout<<"Buy good!(Click any key go on)";
			}
			char c=getch();
			_save();
			
			goto menu3; 
		} else {
			CLEAR;
			if(EN) {
				cout<<"Your ostrakons isn't enough!";
			} else if(SC) {
				cout<<"你的陶片不够了!";
			} else if(CE) {
				cout<<"Your pottery piece not enough!";
			}
			
			goto menu3;
		}
		break;
	case 6:
		break;
	}
}

void getSubdirs(std::string path,vector<string>&files) {
	long long hFile = 0;
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("/*").c_str(), &fileinfo)) != -1) {
		do {
			if((fileinfo.attrib && _A_SUBDIR))
				if(strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					files.push_back(fileinfo.name);
		} while (_findnext(hFile, &fileinfo) == 0);_findclose(hFile);
	}
}

void hide_cursor() {
	HANDLE h_GAME =GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor_info;
	GetConsoleCursorInfo(h_GAME,&cursor_info);
	cursor_info.bVisible=false;
	SetConsoleCursorInfo(h_GAME,&cursor_info);
}

void show_cursor() {
	HANDLE h_GAME =GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor_info;
	GetConsoleCursorInfo(h_GAME,&cursor_info);
	cursor_info.bVisible=true;
	SetConsoleCursorInfo(h_GAME,&cursor_info);
}



void color(const unsigned short color1) {
	/*颜色对应值：
	　　0=黑色              8=灰色　　
	　 1=蓝色                9=淡蓝色               　　
	　　2=绿色              10=淡绿色     0xa      　　
	　　3=湖蓝色       11=淡浅绿色       0xb　
	　　4=红色              12=淡红色      0xc　　
	　　5=紫色              13=淡紫色      0xd     　　
	　　6=黄色              14=淡黄色      0xe     　　
	　　7=白色              15=亮白色      0xf
	　　也可以把这些值设置成常量。
	*/
	if(color1>=0&&color1<=15) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color1);
	} else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
}
