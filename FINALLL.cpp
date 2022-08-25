#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>


using namespace std;


////		forward declaration of classes		////

class User_Interface;
class User;
class AI;
class Admin;
class VI;
class Voter;
class Party;   
class state;
class City;
class Candidate;



/////////////////////////// GLOBAL FUNCTIONS USED  //////////////////////////////
void display();
void clrscr();

void updatevote(Voter V,Candidate cand[],const int x,string ci,string s,int zip);


////////////////////////////////////////////////////////////////////////////////





//////            CLASSES DEFINITIONS            ////////////
class state{
	
		string name_state;
		
	public:
		
		//constructors
		state(const string name_state)
		{  
			this->name_state=name_state;
		}
		state()				//default constructor
		{
			
		}
		
		//  setters getters  
		void setstate(string n)
		{ 
			name_state=n;
		}
		string getstate()const 
		{ 
			return name_state;
		}
		
};
class City:public state{

	string city;
	int ZIP;

	public:
		//  constructors
		City(string city,int ZIP,string s):state(s){ 
			this->city=city;
			this->ZIP=ZIP;
		}
		City(){			//default constructors
			ZIP=0;
		}
		 
		// getters setters
		void setcity(const string city){ this->city=city;}
		string getcity() const{ return city; }
		
		void setzip(const int ZIP){ this->ZIP=ZIP;}
		int getzip() const { return ZIP; }
		
};
class Party{
	
		string party_name;
	
	public:
		//   constructors
		Party(string name){ 
			party_name=name;
		}
		
		Party()		//    default constructors
		{
			
		}
		
		string getpartyname() const { return party_name; }
		void setpartyname(const string s){ party_name=s;}	
				
};

class Candidate:public City,public Party{
	
	string name;
    int code;
	int votes;
	
	static int totalvotes;		//     total votes in the system
	
	public:
		
		//   constructors
		Candidate(const string name,const int  code,const string party,const string state,const string city,const int zip):City(city,zip,state),Party(party){
			this->name=name;
			this->code=code;
			votes=0;						//initializing with the value    '0'
		
		}
	
		//  default constructor
		Candidate(){
			votes=0;						//initializing with the value    '0'
		}
	
		
		//		getters and setters for every attribute
		int getvotes() const { return votes;}
		void setvotes(const int votes){  this->votes=votes;  }
		
		
		string getname() const { return name;}
		void setname(const string name){  this->name=name;	}
		
		void setcode(const int code){  this->code=code;   }
		int getcode() const { return code; }
		
		
		//	member functions for static attribute totalvotes
		static int gettotalvotes() {
			return totalvotes;
		}
		
		static void updatetotalvotes(const int x){
			totalvotes+=x;
		}	
		
		
		//	other member functions
		void updatevote(const int x){
			votes+=x;
		}
		
		
		
		void countvotes(){			//counts votes of every individual candidate
			
			int c;
			long int id;
			
			
			ifstream fp("idcodes.txt");		//     file 'idcodes.txt' contains the    ID and code(of candidate) of the users who confirmed and finalized their vote
			
			
			if (!fp){
				cout<<"Cannot open the file";
			}
			else{

				while(!fp.eof()){
						fp>>id;
						fp>>c;
						
						
						if(c==code){
							votes++;
						}
	
							
				}
				
			}
			
			
			fp.close();
		}
		
		void listvoters(){			//lists ids of voters of the candidate
			int c;
			long int id;
			
			ifstream fp("idcodes.txt");
			if (!fp){
				cout<<"Cannot open the file";
			}
			else{
				cout<<"Reading data now\n";
			
				while(!fp.eof()){
					fp>>id;
					fp>>c;
					
					if(c==code){
						cout<<id<<endl;
					}	
				}
				
			}
				
			fp.close();
				
						
		} 
		
		//    friend func to update the vote whenthe voter confirms its vote
		
		friend void updatevote(Voter V,Candidate cand[],const int x,string ci,string s,int zip);
		
};


int Candidate::totalvotes=0;


class User_Interface{
	
	public:
		
		static void displaymain(){
			display();
		}
		static void mainmenu() 
		{
			cout<<"******************************************  WELCOME TO ONLINE ELECTORAL SYSTEM  ******************************************"<<endl<<endl<<endl<<endl<<endl<<endl;
			cout<<"			Select one of the options"<<endl;
			cout<<"			1.Admin"<<endl;
			cout<<"			2.Voter"<<endl;
		}
		
		
		void voterspage()const {
			cout<<"********************************************   VOTER'S PANEL   ***********************************************"<<endl<<endl<<endl<<endl<<endl<<endl;
		} 
		void adminpage() const {
			cout<<"********************************************   ADMIN'S PANEL   **********************************************"<<endl<<endl<<endl<<endl<<endl<<endl;
		}
	
		
};
class User:public User_Interface
{
	protected:
		long int id;
		string password;
		
		
	public:
		User()			//default constructors
		{
			
		}
		
		//  members functions 
        void signin()	
        {
        	
		}
		
		//getters and setters of every data member
		void setid(const long int id)	
		{
			this->id=id;	
		}
			
		long int getid  ()	const
		{	return id;	}
		
		
		void setPassord(const string p)
		{	
			password=p;
		}
		string getPassword()const {	return password;	}
		
		
		
		// 		function to set the name of the state , city and the zip code accord the user's choice 
		void select_state_city(string *ci,string *s,int *zip){				
			
			int option,c_option;
			
			
			cout<<"Select your state and city\n\n";
			cout<<"States   \n\n1.Colorado   \n2.Alabama  \n3.Florida  \n";
			cin>>option;
			
			
			//setting names of the states and cities
			switch(option){
				
				case 1:{
					cout<<"\n\nSelect City  \n\n 1.Denver(888)   \n 2.Boulder(899)   \n 3.Aspen(877)\n";
					*s="Colorado";
					
					do{
						cin>>c_option;
						if(c_option==1){
							
								*ci="Denver";
								*zip=888;
								break;
							
						}
						else if(c_option==2){
							
								*ci="Boulder";
								*zip=899;
								break;
						}
						else if(c_option==3){
							
								*ci="Aspen";
								*zip=877;
								break;
						}
						else
								cout<<"Try again :  ";
							
							
					}while(c_option!=1||c_option!=2||c_option!=3);
					break;
				}
				
				case 2:{
					cout<<"\n\nSelect City  \n\n 1.Birmingham(233)   \n 2.Mobile(244)   \n 3.Dothan(266)\n";
					*s="Alabama";
						
					do{
						cin>>c_option;
						
						if(c_option==1){
								*ci="Birmingham";	
								*zip=233;
								break;
						}
						else if(c_option==2){
								*ci="Mobile";
								*zip=244;
								break;
						}
						else if(c_option==3){
								*ci="Dothan";
								*zip=266;
								break;
						}
						else
								cout<<"Try again :  ";
							
					}while(c_option!=1||c_option!=2||c_option!=3);
					break;
				}
				
				case 3:{
					cout<<"\n\nSelect City      \n\n 1.Miami(454)    \n 2.Tampa(757)    \n 3.Naples(959)\n";
					*s="Florida";
						
					do{
						cin>>c_option;
						
						if(c_option==1){
								*ci="Miami";
								*zip=454;
								break;
						}
						else if(c_option==2){
								*ci="Tampa";
								*zip=757;
								break;
						}
						else if(c_option=3){
								*ci="Naples";
								*zip=959;
								break;
						}
						else
								cout<<"Try again :  ";
							
					}while(c_option!=1||c_option!=2||c_option!=3);
					break;
				}
				
				default:{
					cout<<"\nIncorrect choice\n";
					break;
				}
			}
		}
		
		//func for input masking of password on the console
		void inputmasking(string *password){
				char c;
				
				
				while (true)
				{	
				
					c=getch();
					if (c!='\b'  &&  c!='\r'){
						password->push_back(c);
						putch('*');
					}
					else if(c=='\b'){
						if(password->size()!=0){
							password->erase(password->size()-1);
							cout<<"\b \b";
					
						}
					}
					else if (c=='\r'){
						break;
					}
				}	
		}
		
		void generatereport(string *p,int *p_votes,Candidate c[],const int x){					// generates report for the winning party
		
			
					//updating votes for every party
					for(int j=0;j<3;j++){
						for(int i=0;i<x;i++){
							if(p[j]==c[i].getpartyname()){
								p_votes[j]+=c[i].getvotes();
							}
						}	
					}	
					 
					
					int max=0;
					string k;
					
					
					//finding the winning party
					for(int j=0;j<3;j++){
						if(p_votes[j]>max){
							max=p_votes[j];
							k=p[j];
						}
					}
					cout<<endl<<endl;
		
					
					//Calculating percentage for the winning party
					float percentage;
					percentage=float(max)/float(Candidate::gettotalvotes())*100;
				
				
					cout<<"\n\n\n\n\n";
					
					cout<<"\t\t\t"<<"******************************************************************************"<<endl;
					cout<<"\t\t\t"<<"*****************                                         ********************"<<endl;
					cout<<"\t\t\t"<<"*****************            WINNING                      ********************"<<endl;
					cout<<"\t\t\t"<<"*****************             PARTY                       ********************"<<endl;
					cout<<"\t\t\t"<<"*****************              IS                         ********************"<<endl;
					cout<<"\t\t\t"<<"*****************                                         ********************"<<endl;
					cout<<"\t\t\t"<<"*****************                                         ********************"<<endl;
					cout<<"\t\t\t"<<"*****************                                         ********************"<<endl;
					cout<<"\t\t\t"<<"*****************                                         ********************"<<endl;	
					cout<<"\t\t\t"<<"*****************              "<<k<<"                         ********************"<<endl;
					cout<<"\t\t\t"<<"*****************                                         ********************"<<endl;
					cout<<"\t\t\t"<<"*****************                                         ********************"<<endl;
					cout<<"\t\t\t"<<"*****************             "<<fixed<<setprecision(1)<<percentage<<"%                       ********************"<<endl;
					cout<<"\t\t\t"<<"*****************                                         ********************"<<endl;
					cout<<"\t\t\t"<<"*****************                                         ********************"<<endl;
					cout<<"\t\t\t"<<"*****************              seats                      ********************"<<endl;
					cout<<"\t\t\t"<<"*****************                                         ********************"<<endl;
					cout<<"\t\t\t"<<"*****************                                         ********************"<<endl;
					cout<<"\t\t\t"<<"*****************                                         ********************"<<endl;
					cout<<"\t\t\t"<<"*****************                                         ********************"<<endl;
					cout<<"\t\t\t"<<"*****************                                         ********************"<<endl;
					cout<<"\t\t\t"<<"*****************                                         ********************"<<endl;
					cout<<"\t\t\t"<<"******************************************************************************"<<endl;
				
	}
};


class VI{				//abstract class ---  Interface class ----   for Voter panel
	public:
		virtual void signin()=0;
		virtual void signup()=0;
		
};
class Voter:public User,public VI{
	int vote;
	int zip;
	
	public:
		Voter(){		//default constuctor  and initializing the data members   vote and zip  with value '0'
			vote=0;
			zip=0;
		}
		
		//getters and setters for every data member
		void setVote(const int vote){
			this->vote=vote;
		}
		int getVote() const {return vote;}
		
		void setzip(const int zip){
			this->zip=zip;
		}
		int getzip()const { return zip;}
		
		
		//     friend func to update the voter if voter confirmed to update the vote in real time
		friend void updatevote(Voter V,Candidate cand[],const int x,string ci,string s,int zip);
    	
    	
    	
    	//     definitions of other member functions
		
		void signin()
		{
			clrscr();
			
			string *p=new string [400];
			long int *iidd=new long int[400];
			int z[400];
			int i=0,count=0;
			
			
			
			//id  ==  User::id
			//password == User::password
			//zip == Voter::zip
			//vote == Voter::vote
				
											
			
			cout<<"\t\tWelcome to SIGN-IN PAGE\t\t"<<endl<<endl<<endl;
		
			cout<<"Enter ID: ";
			cin>>id;
			
			cout<<"Enter password :";
			fflush(stdin);
			
			password.clear();
			User::inputmasking(&password);						/*Input masking of password*/
														
			
			ifstream fp("idpass.txt");									/*To load the user database from the file "idpass.txt" into memory */
			
			
			if (!fp){
				cout<<"Cannot open the target file";
				exit(0);
			}
			
			else
			{
				while(!fp.eof()) {
				 fp>>iidd[i];
				 fp>>z[i];
				 fp>>p[i];
				 count++;
				 i++;
			   }
			}
		
			fp.close();
			
			
			int code;
			long int ID;
			bool voted=false,found=false;
			
			
			for(i=0;i<count;i++)
			{											/*To verify the sign in of user*/
				if(iidd[i]==id)
				{	
						
							if(zip==z[i]){				//to check if the state and city entered is correct			// zip   ==   Voter::zip
									if (p[i].compare(password)==0)
									{
										
										cout<<"\n\n\n\n\n\t\t		SIGN IN SUCCESSFUL!!\n\n\n\n";
										
										
										ifstream FP2("idcodes.txt");							/*To check if Voter has already voted from the files "idcodes.txt" */
										
										if (!FP2)
										{
											cout<<"Cannot open the target file";
											exit(2);
									    }
									    while(!FP2.eof()) 
										{
									        FP2>>ID;
									        FP2>>code;
									        
									        
											if (ID==iidd[i] ){
											
												cout<<"\n\t\t		You have already Voted!!"<<endl;
												cout<<"\n\t\t		The person you voted for is:"<<code<<endl;
												vote=code;
												voted=true;
												break;
											
											}
											else
												voted=false;
										
										}
										
										FP2.close();
										
										
												
										if (voted==false)
										{
											vote=0000;										/*If the user has not voted yet ,set vote to '0'  */
										}
										
										found=true;
										break;
										
									}
									else
										found=false;
							}
							else{													//if incorrect state or city (the one which the user donot belong to) entered by user
								
								
								cout<<"\n\t\tIncorrect state/city\n";
								cout<<"\t\tDo you want to try again\n(Enter Y is yes ,Press any other key to continue) ";
								if(getch()=='y'||getch()=='Y')	
									signin();
								else{
									clrscr();
									cout<<"\n\n\n\t\tSee you again soon";
									exit(5);
								}
								
								
							}
							
			    }
			    
				else 
						found=false;		
			
			}
			
			
			if (found==false)
			{
				cout<<"\n\n\n\tID OR PW WRONG";
				cout<<endl<<"\tDo you want to try again?(y to continue) ";  
				if(getch()=='y'||getch()=='Y')
					signin();
				else
					exit(1);
			}
			
			
			delete[] iidd;
			delete[] p;		
								
    		
		}
		void signup(){
				clrscr();
				
				int i=1,count=0;
				string pass;			//temporary variable to store the re enterd password
				
										//id  ==  User::id
										//password == User::password
										//zip == Voter::zip
										//vote == Voter::vote
				
				long int i_d;
				string p_w;
				int zi;
				
				bool found=false;
				
				
				ifstream f("idpass.txt");
				if(!f){
					cout<<"\ncannot opem the file\n";
					exit(1);
				}
									
									
									
				cout<<"\n\t\tWelcome to SIGN UP PAGE\t\t\n\n\n";
				cout<<"Enter ID(8 digits only)(100000000):";
				
									//checking if the id already exists(is user already signed-up)
				do{
						cin>>id;
						while(!f.eof()){
							f>>i_d;
							f>>zi;
							f>>p_w;
							if(i_d==id){
								found=true;
								break;
							}
							else{
								found=false;
							}
						}
						
						if(found==true){
							cout<<"\nID already exists ,enter the ID again\n";
						}
				}while(found==true);
				
				f.close();
				
				
				long int ii_d;
				bool approved=false;
				int z;
				
				
															
				if ((id/10000000!=0)&&(id/10000000<10)){						//id==User::id
					if((double)id<=(double)99999999){
							
							//check if person is valid user
							ifstream fin("ID.txt");
							
							if(!fin){
								cout<<"\n		Error opening the file";
								exit(0);
							}
							
							while(!fin.eof()){
								fin>>ii_d;
								fin>>z;
								if(ii_d==id){
									approved=true;
									break;
								}
							}
							
							fin.close();
							
							
							//prompt to sign in again if invalid id entered
							if(approved==false){
								cout<<"\t\tInvalid id\n\n\t\tTry again?(y/n) :";
								if(getch()=='y'||getch()=='Y')
									signup();
									
								else if (getch()=='n'||getch()=='N')
									exit(2);
							}
							
							
							//prompt if correct city or state entered(the one user donot belongs to)
							if(zip!=z){															//zip == Voter::zip
								cout<<"\n\t\tIncorrect state/city\n";
								cout<<"\t\tDo you want to try again\n(Enter Y is yes ,Press any other key to continue) ";
								if(getch()=='y'||getch()=='Y')	
									signup();
									
								else{
									clrscr();
									cout<<"\n\n\n\t\tSee you again soon";
									exit(5);
								}
							}
							
							
							
							cout<<"Enter the password(min 6 digits) : ";
							do{
								password.clear();
								fflush(stdin);
								User::inputmasking(&password);							//password == User::paswword
								
								if(password.length()<6)
									cout<<"\nEnter pw again(atleast 6 digits): ";
						
							}while(password.length()<6);							//length of password should be more than   '6'
							
							cout<<"\nRe-Enter your password: ";
							fflush(stdin);
							User::inputmasking(&pass);
							
							if (pass.compare(password)==0)
								goto store_userdata;			/*Stores user's data into the file*/
							else
								cout<<"\nPw donot match";
					}
					
					else
					{
						cout<<endl<<endl<<"ID entered in incorrect format!";
						goto incorrect_formatid;								/*Prompt to sign up again or end the program*/
					}
				}
				
				else{
						cout<<endl<<endl<<"ID entered in incorrect format!";
						goto incorrect_formatid;									/*Prompt to sign up again or end the program*/						
				}
	
	
		incorrect_formatid:
					{
					char c;
						
					cout<<"\nDo you want to try again(Y/N)? ";
					c=getch();
					
					if((c=='y')||(c=='Y')){
						clrscr();
						signup();						         //If user wants to sign up again //
					}
					else if ((c=='n')||(c=='N'))
						exit(4);
					else {
						cout<<"\nError:Sorry cannot update the contents!";
						exit(4);
					}
				}
		
		store_userdata: {
						
						fstream fp("idpass.txt",ios::app);
						if (!fp){
							cout<<"Cannot open the target file";
							exit(1);
						}
						
						//writing into the file "Userdata.txt" 
						while(1){
							fflush(stdin);			
							fp<<id<<'\t';
							fp<<zip<<'\t';
							fp<<password<<endl;
							break;
						}
						
						printf("\nData updated!\n");
						fp.close();
				
    	}
	}
		//		displays details of the  candidate with requested state and city
		void displaying_cand_details(Candidate c[],const int x,string s,string ci,int zip){	
			
			cout<<endl<<endl<<"The candidates for "<<ci<<" ("<<zip<<") "<<s<<" are: "<<endl<<endl;
			
			int j=1;
			
			for(int i=0;i<x;i++){
				if(s==c[i].getstate() && ci==c[i].getcity()&& zip==c[i].getzip()){
					cout<<j<<".   "<<c[i].getcode()<<"\t\t"<<c[i].getname()<<string(25-c[i].getname().size(),' ')<<c[i].getpartyname()<<endl;
					j++;
				}
			}
			
			
		}
};


class AI{				//abstract class ---  Interface class ---- for Admin panel
	public:
		virtual void Admin_menu()=0;
		virtual void winningcand(Candidate c[],const int x)=0;
		virtual void display_cand_data(Candidate c[],const int x)=0;
		virtual void listvoters(Candidate c[],const int x,int code)=0;
		virtual void display_all_data()=0;
		virtual void partystatus(string *p,int *p_votes,const int x)=0;
				
};
class Admin:public User,public AI
{
	const long int adminid;
	const string adminpass;

	public:
		
		//		default constructor ,initialising values 
		Admin():adminid(12349876),adminpass("22334455")
		{
			   
		}
		
		
		//////////////       other member functions         ///////////////
		
		//			displays the options available for the admin (ADMIN'S RIGHTS) 
		void Admin_menu() {
			cout<<"\n\n\nSelect one of the following options\n\n";
			cout<<"1.Display all user data\n";
			cout<<"2.Display winning candidate\n";
			cout<<"3.Display list of voters a certain Candidate\n";
			cout<<"4.Display status of all parties\n";
			cout<<"5.Display All Candidate's data\n";
			cout<<"6.Exit\n";
		}
		
		void signin ()
		{
			
			cout<<"Enter Admin ID: ";
			cin>>id;
			cout<<"Enter password:";
			fflush(stdin);
			User::inputmasking(&password);	
			
			
			if(id==adminid){						//  	id ->  User::id
				if(password==adminpass){			//		password -> User::password
					cout<<"\n\n\t\t\tLogged in successfully!\n";
				}
				else{
					cout<<"\nIncorrect pw"<<endl;
					cout<<"ACCESS DENIED"<<endl;
					exit(2);
				}
					
			}
			
			else{
				cout<<"Access denied!!";
				exit(2);
			}
				
		}
		
		//		displays anme and no.of votes or all parties     ///
		void partystatus(string *p,int *p_votes,const int x){
			cout<<"\n\n\t\t"<<string(8,'*')<<"Displaying party status "<<string(8,'*')<<"\n\n\n";
			cout<<"\n\t\t\tParty	    votes\n\n";
			for(int i=0;i<x;i++){ 
				cout<<"\t\t\t"<<p[i]<<"	     "<<p_votes[i]<<endl;
			}
		}
		
		//		displays winning candidate 	  //
		void winningcand(Candidate c[],const int x){
			int MAX=0,K;
	
			for(int i=0;i<x;i++){
				if(c[i].getvotes()>MAX){
					MAX=c[i].getvotes();
					K=i;
				}
			}
			
			
			
			clrscr();
			cout<<"\n\n\n";
			cout<<"**************************************************************"<<endl;
			cout<<"**************************************************************"<<endl;
			cout<<"**************************************************************"<<endl;
			cout<<"****************                        **********************"<<endl;
			cout<<"****************   WINNING CANDIDATE    **********************"<<endl;
			cout<<"****************                        **********************"<<endl;
			cout<<"**************************************************************"<<endl;
			cout<<"**************************************************************"<<endl;
			cout<<"**************************************************************"<<endl;
			
			cout<<"\n\n\n\n\n\n**************************************************************"<<endl;
			cout<<"\n\n\n\t\tThe winning candidate is \n\n\t\t\t "<<c[K].getname()<<" \n\n\t\t\t ("<<c[K].getpartyname()<<")"<<endl;
			cout<<"\n\n\n**************************************************************"<<endl;
		}
		
		//   displays data of the voters  (id  pw  and code (of the candidate they voted for) )//
		void display_all_data(){
					int choice;
					
					//variables to store the data of file "alldata.txt"
					long int id;
					int code,zip;
					string pw;
					
					//variables to store the data of files "idcode.txt and idpass.txt"
					long int I,idd;
					string pass;
					int z;
					bool found=false;
					
					
					cout<<"select one:"<<endl<<"1.Details of all the voters "<<endl<<"2.Details of voters with state and city"<<endl;
					do{
						cin>>choice;
					
						switch(choice){
								case 1:{
									
									ifstream fp("alldata.txt");
									if(!fp){
										cout<<endl<<"error in opening the file 'alldata.txt' ";
										exit(0);
									}	
									
									cout<<"   ID    "<<'\t'<<"CODE"<<'\t'<<"     PW     "<<endl<<endl;
									
									
									while(fp>>id>>zip>>code>>pw){			//to display data of the users who have already voted	
										cout<<endl<<id<<"	"<<code<<"	"<<pw;
									}
									fp.close();
									
									
									ifstream f("idcodes.txt");
									if(!f){
										cout<<endl<<"error in opening the file 'idcodes.txt' ";
										exit(0);
									}
									
									ifstream F("idpass.txt");
									if(!F){
										cout<<endl<<"error in opening the file 'idpass.txt' ";
										exit(0);
									}
						            
									cout<<endl;
									
									
									
									//		to display data of the voters who have not voted yet
									while(F>>I>>z>>pass)
									{
										found=false;
										
										while(f>>idd)
									    {
									    	if(I==idd)
									    	{
									    		found=true;
									    		break;
											}
										}
										
										if(!found)										//checks if the id found in 'codes.txt' or not
											cout<<I<<"	"<<"----"<<"	"<<pass<<endl;  //if not found , outputs the id and password 
										
									}
							
									f.close();
									F.close();
									
									break;
								}
								case 2:{
										
										string city,state;
										int zipp;
										select_state_city(&city,&state,&zipp);
										
										clrscr();
										cout<<"\n\nVoters of  "<<city<<" ("<<zipp<<")  ,"<<state<<endl<<endl<<endl;
	
	
										cout<<"   ID    "<<'\t'<<"CODE"<<'\t'<<"     PW     "<<endl<<endl;
										
										ifstream fp("alldata.txt");
										if(!fp){
											cout<<endl<<"error in opening the file 'alldata.txt' ";
											exit(0);
										}	
										
										while(fp>>id>>zip>>code>>pw){			//to display data of the users who have already voted	
											if(zipp==zip)
											{
												cout<<endl<<id<<"	"<<code<<"	"<<pw;
											}
										}
										fp.close();	
										
										
										ifstream f("idcodes.txt");
										if(!f){
											cout<<endl<<"error in opening the file 'idcodes.txt' ";
											exit(0);
										}
										
										ifstream F("idpass.txt");
										if(!F){
											cout<<endl<<"error in opening the file 'idpass.txt' ";
											exit(0);
										}
							           
									    
									    //		to display data of the voters who have not voted yet
										cout<<endl;
										while(F>>I>>z>>pass)
										{
											found=false;
											
											while(f>>idd)
										    {
										    	if(I==idd)
										    	{
										    		found=true;
										    		break;
												}
											}
											
											
											if(!found)			
											{
												if(z==zipp)				//		checks if the user has the same zip as the requested  'zip'  (determined by the state and city requested)
													cout<<I<<"	"<<"----"<<"	"<<pass<<endl;  
											}
											
										}
								
										f.close();
										F.close();
										break;
								}
								default:{
									cout<<"\n\tEnter the correct choice : ";
									break;
								}
								
						}	
					}while(choice!=1 && choice!=2);
			      
			      	
		}
		
		//   displays data of the candidate   i.e,  code   , name   and no of votes of the candidate  ///
		void display_cand_data(Candidate c[],const int x){
					string *state=new string[3];			//array of states
		
					string **city=new string*[3];			//array of pointers
					
					for(int i=0;i<3;i++){					//allocating memory 
						city[i]= new string[3];
					}
					
					//		storing cities
					city[0][0]="Denver";
					city[0][1]="Boulder";
					city[0][2]="Aspen";
					
					city[1][0]="Birmingham";
					city[1][1]="Mobile";
					city[1][2]="Dothan";
					
					city[2][0]="Miami";
					city[2][1]="Tampa";
					city[2][2]="Naples";
					
					
					//		storing states
					state[0]="Colorado";
					state[1]="Alabama";
					state[2]="Florida";
					
					
					//Displaying data ccording to every city and state
					for(int i=0;i<3;i++){
						cout<<endl<<endl<<"\n\n\t\t\t"<<string(13,'*')<<state[i]<<string(13,'*')<<endl;
						
						for(int j=0;j<3;j++){
							cout<<endl<<endl<<"\t\t\t"<<city[i][j]<<':'<<endl;
							
							for(int k=0;k<x;k++){
								if(state[i]==c[k].getstate() && city[i][j]==c[k].getcity()){
									cout<<endl<<"\t\t\t"<<c[k].getcode()<<'\t'<<c[k].getname()<<string(25-c[k].getname().size(),' ')<<c[k].getvotes();
								}
								
							}	
						}
					}
					
					
					//freeing the memory
					for(int i=0;i<3;i++){
						delete [] city[i];
					}
					delete [] city;
					delete [] state;

		}
		
		//		displays the ids of voters of the requsted candidate   //
		void listvoters(Candidate c[],const int x,int code){
			for(int i=0;i<x;i++){
				if(c[i].getcode()==code)
					c[i].listvoters();
			}
		}
		
};

class Electionday{
	Candidate c[27];
					 
	string *party;
	int *partyvotes;
	
	
	public:
		Electionday(){
			party=new string[3];
			partyvotes= new int[3];
			
			party[0]="NA";
			party[1]="PA";
			party[2]="PKT";
			
			for(int i=0;i<3;i++)
				partyvotes[i]=0;
				
				//		initialising candidates' data		//
				
				c[0]=     Candidate("Adam Blakes",1200,"NA","Colorado","Denver",888);
				c[1]=	 Candidate("Maria Jones",1222,"PA","Colorado","Denver",888);
				c[2]=	 Candidate("Alan Jake",1999,"PKT","Colorado","Denver",888);
				c[3]=	 Candidate("Jack Morton",2222,"PA","Colorado","Boulder",899);
				c[4]=	 Candidate("Gabrielle Johnes",2000,"NA","Colorado","Boulder",899);
				c[5]=	 Candidate("Doran Lloyd",2999,"PKT","Colorado","Boulder",899);
				c[6]=	 Candidate("Raylon Griffin",3222,"PA","Colorado","Aspen",877);
				c[7]=	 Candidate("LeMaun Boone",3000,"NA","Colorado","Aspen",877);
				c[8]=	 Candidate("Jaimeson Smith",3999,"PKT","Colorado","Aspen",877);
				c[9]=	 Candidate("Finton Hunter",9222,"PA","Alabama","Birmingham",233);
				c[10]=	 Candidate("Zebulee Mckinney",9000,"NA","Alabama","Birmingham",233);
				c[11]=	 Candidate("Tario Mcdowell",9999,"PKT","Alabama","Birmingham",233);
				c[12]=	 Candidate("Kenvante Bell",4222,"PA","Florida","Miami",454);
				c[13]=	 Candidate("Kincade Peters",4000,"NA","Florida","Miami",454);
				c[14]=	 Candidate("Varnan Daniels",4999,"PKT","Florida","Miami",454);
				c[15]=	 Candidate("Dyonte Wiley",5222,"PA","Florida","Tampa",757);
				c[16]=	 Candidate("Latrelle Powell",5000,"NA","Florida","Tampa",757);
				c[17]=	 Candidate("Rhad Epps",5999,"PKT","Florida","Tampa",757);
				c[18]=	 Candidate("Troylen Terry",6222,"PA","Florida","Naples",959);
				c[19]=	 Candidate("Thayne Porter",6000,"NA","Florida","Naples",959);
				c[20]=	 Candidate("Vequain Ramsey",6999,"PKT","Florida","Naples",959);
				c[21]=	 Candidate("Rhad Sullivan",7222,"PA","Alabama","Dothan",266);
				c[22]=	 Candidate("Kyrton Lawson",7000,"NA","Alabama","Dothan",266);
				c[23]=	 Candidate("Reilly Sullivan",7999,"PKT","Alabama","Dothan",266);
				c[24]=	 Candidate("Jamyron Lee",8222,"PA","Alabama","Mobile",244);
				c[25]=	 Candidate("Wendall Starks",8000,"NA","Alabama","Mobile",244);
				c[26]=	 Candidate("Leeshawn White",8999,"PKT","Alabama","Mobile",244);
		}
		//destructor
		~Electionday(){
			delete [] party;
			delete [] partyvotes;
		}
		
		
		//	updates votes of every candidate 
		void updatingvotes(){
			
			for(int j=0;j<27;j++){
				c[j].countvotes();
				Candidate::updatetotalvotes(c[j].getvotes());
			}
			
		}
		
		//             function to be called when Voter panel requested  by the user     //
		void voterspanel(){
		
			int choice,zip,s_option,c_option;
			string city,state;	
			Voter voter;
			
			clrscr();
			voter.voterspage();
			
			
			voter.select_state_city(&city,&state,&zip);
			clrscr();
			cout<<"\n\n\n\n\n";
			
			
			voter.setzip(zip);
			
			
			//Prompting for sign in or sign up
			cout<<"Enter \n\t1.Sign in. \n\t2.Sign up. "<<endl;
			do{
				cin>>choice;
			
				if(choice==1){
					clrscr();
					voter.voterspage();
					voter.generatereport(party,partyvotes,c,27);
					
					
					cout<<endl<<endl<<endl<<"					Press any key to continue   ";
					getch();
					clrscr();
					
					voter.voterspage();
					voter.signin();
				
				
					if(voter.getVote()==0000){
						updatevote(voter,c,27,city,state,zip);
					}

					
					break;
				}
				else if(choice==2){
						clrscr();
						voter.voterspage();
						voter.generatereport(party,partyvotes,c,27);
						cout<<"\n\n\n\t\t\tenter any key to continue";
						getch();
						clrscr();
						
						
						voter.voterspage();
						voter.signup();
						cout<<endl<<"DO YOU WANT TO VOTE RIGHT NOW(Enter Y to continue,press any other key to exit)?\n";
						
						
						
						if(getch()=='y'||getch()=='Y')
							updatevote(voter,c,27,city,state,zip);
						
						else{
							
							clrscr();
							cout<<endl<<endl<<endl<<endl<<"               	SEE"<<endl;
							cout<<"                 YOU"<<endl;
							cout<<"                 SOON ";
							
							exit(0);
						}
						break;
				}
				else 
					cout<<"\n\nTry again";
					
			}while(choice!=1||choice!=2);
			
				getch();
				exit(0);
		}
		
		//             function to be called when Admin Panel requested byb the user	//
		void Adminpanel(){
			
			
			
			Admin admin;
			
			admin.adminpage();
			admin.signin();
			cout<<endl<<endl<<endl<<"					Press any key to continue   ";
			getch();
			clrscr();
			
			
			
			admin.adminpage();
			admin.generatereport(party,partyvotes,c,27);
			
			cout<<endl<<endl<<endl<<"					Press any key to continue   ";
			getch();
			clrscr();
			
			cout<<"\n\n\n";
			
			int choice;
			
			do{
				admin.Admin_menu();
				cin>>choice;
				
				switch(choice){
					case 1:{
						clrscr();
						admin.display_all_data();
						
						cout<<endl<<endl<<"Enter any key to continue";
						getch();
						clrscr();
						break;
					}
					
					case 2:{
						
						clrscr();
						admin.winningcand(c,27);
						
						cout<<endl<<endl<<"Enter any key to continue";
						getch();
						clrscr();
						break;
					}
					
					case 3:{
						
						clrscr();
						cout<<"Displaying all candidates\n\n";
						for(int i=0;i<27;i++){
							cout<<c[i].getname()<<string(20-c[i].getname().size(),' ')<<c[i].getcode()<<endl;
						}
						
						
						bool correct=false;
						int codeee;
						cout<<"Enter the code of candidate you want the list of voters of \n";
							
						do{
							cin>>codeee;
							for(int i=0;i<27;i++){
								if(c[i].getcode()==codeee){
									correct=true;
									break;
								}
								else 
									correct=false;
							}
							
							if(correct==false)
								cout<<"\ntry again : ";
								
						}while (correct==false);
						
						
						clrscr();
						admin.listvoters(c,27,codeee);
						
						
						cout<<endl<<endl<<"Enter any key to continue";
						getch();
						clrscr();
						break;
					}
					
					case 4:{
						clrscr();
						
						admin.partystatus(party,partyvotes,3);
						
						cout<<endl<<endl<<"Enter any key to continue";
						getch();
						clrscr();
						break;
					}
					
					case 5:{
						clrscr();
						
						admin.display_cand_data(c,27);
						
						cout<<endl<<endl<<"Enter any key to continue";
						getch();
						clrscr();
						break;
					}
					
					case 6:{
						clrscr();
						cout<<endl<<endl<<endl<<endl;
						cout<<endl<<endl<<"				Exitting the Admin Panel";
						exit(0);
						break;
					}
					
					default:{
						clrscr();
						cout<<"\n\t\t\tIncorrect choice"<<endl;
						cout<<"\t\t\tEnter again ";
						
						break;
					}
				}
				
			}while(choice!=6);
			
		}
		
		void main_page(){
			int choice;
			User_Interface::mainmenu();
		
		
		
			//updating votes of every cand	
			updatingvotes();						// 		updatingvotes() --> Electionday::updatingvotes()
					
			do{
					cin>>choice;
					if(choice==2){
						clrscr();
						Electionday::voterspanel();
						
					}	
					else if(choice==1){
						clrscr();
						Electionday::Adminpanel();
					}
					else
						cout<<"\n\t\t\tIncorrect option selected\n\n\t\t\t\tTRY AGAIN\n";
						
			}while(choice!=1&&choice!=2);
			
		}
};



////////////////////////////////////////////////////////////////////
//friend function
void updatevote(Voter V,Candidate cand[],const int x,string ci,string s,int zip){
		
					int i=2;
					bool correctvote=false;
					cout<<"(Note:You can only vote once !)\n";
				
					int choice;
					
					
					fstream FP3("idcodes.txt",ios::app);
					if (!FP3){
						cout<<"Cannot open the target file 'idcodes.txt'";
						exit(3);
					}
					
					do{
							V.displaying_cand_details(cand,x,s,ci,zip);		//getting list of candidates having the same state ,city and zip code
							cout<<endl<<endl<<"Enter the code: ";
							cin>>V.vote;
							
							
							for(int i=0;i<x;i++){
								if(cand[i].getstate()==s&&cand[i].getcity()==ci&&cand[i].getzip()==zip){
									
									if(V.vote==cand[i].code){		//check if the vote of the Voter matches the votecode of candidate
										correctvote=true;
										cand[i].updatevote(1);
										cand[i].updatetotalvotes(1);
										break;
									}
									else{
										correctvote=false;
									}
									
								}
							}
							
							
							//prompts for the confirmation to save the file
							if(correctvote==true){
								cout<<"\nEnter '1' to confirm\nEnter '2' to Vote again\n";
								cin>>choice;
							}
							else
								cout<<"\nIncorrect code \nEnter correct code\n";		//prompts to enter the code again in case of incorrect code
					
					
					}while(((choice!=1)&&(choice==2))||choice==false);
			              
					fstream fpp("alldata.txt",ios::app);
					if(!fpp){
						cout<<"\n  Error in opening the file 'alldata.txt'";
						exit(0);
					}		
					
					
					if(choice==1){
						FP3<<V.id;
						FP3<<"\t"<<V.vote<<endl;						//Writing the contents into the file
						
						fpp<<V.id<<'\t';
						fpp<<V.zip<<'\t';
						fpp<<V.vote<<'\t';
						fpp<<V.password<<endl;
					}
					
					cout<<"\n\n\t\tVOTE UPDATED";
					FP3.close();
					fpp.close();
					exit(0);
	}
	


/////////////////////////////////////////////////////////////////////


//      clearing the screen      //

void clrscr(){
    system("@cls||clear");
}


/*Color definitions for console background*/

#define BLUE    "\x1b[34m"
#define CYAN    "\x1b[36m"

///////////////////////////////////////////////////////////////////////////////////////////////
void display()
{	
	
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_SHOWMAXIMIZED);
	
	system("COLOR 7F");
	printf("\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t");
	printf(CYAN "\n\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2"BLUE);
	printf(CYAN "\n\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2"BLUE);
	printf(CYAN "\n\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf(CYAN "\n\t\t\t\t\xB3\xB3                                                          \t\xB3\xB3");
	printf(BLUE "\n\t\t\t\t\xB3\xB3                                                          \t\xB3\xB3");
	printf(BLUE "\n\t\t\t\t\xB3\xB3                                                          \t\xB3\xB3");
	printf(BLUE "\n\t\t\t\t\xB3\xB3                                                          \t\xB3\xB3");
	printf(BLUE "\n\t\t\t\t\xB3\xB3                                                          \t\xB3\xB3");
	printf(BLUE "\n\t\t\t\t\xB3\xB3                                                          \t\xB3\xB3");
	printf(BLUE "\n\t\t\t\t\xB3\xB3                                                          \t\xB3\xB3");
	printf(BLUE "\n\t\t\t\t\xB3\xB3                                                          \t\xB3\xB3");
	printf(BLUE "\n\t\t\t\t\xB3\xB3                                                          \t\xB3\xB3");
	printf(BLUE "\n\t\t\t\t\xB3\xB3                	''  W E L C O M E  ''                  \t\xB3\xB3");
	printf(BLUE "\n\t\t\t\t\xB3\xB3                      	                               \t\xB3\xB3");
	printf(BLUE "\n\t\t\t\t\xB3\xB3                 	    '' T O ''                       \t\xB3\xB3");
	printf(BLUE "\n\t\t\t\t\xB3\xB3                  	                                  \t\xB3\xB3");
	printf(BLUE "\n\t\t\t\t\xB3\xB3                 	'' O N L I N E ''     	        \t\xB3\xB3");
	printf(BLUE "\n\t\t\t\t\xB3\xB3                      	                             \t\xB3\xB3");
	printf(BLUE "\n\t\t\t\t\xB3\xB3                     ''E L E C T O R A L''               \t\xB3\xB3");
	printf(BLUE "\n\t\t\t\t\xB3\xB3                  	                                  \t\xB3\xB3");
	printf(BLUE "\n\t\t\t\t\xB3\xB3                	''  S Y S T E M ''                     \t\xB3\xB3");
	printf(BLUE "\n\t\t\t\t\xB3\xB3                                                          \t\xB3\xB3");
	printf(BLUE "\n\t\t\t\t\xB3\xB3                                                          \t\xB3\xB3");
	printf(BLUE "\n\t\t\t\t\xB3\xB3                                                          \t\xB3\xB3");
	printf(BLUE "\n\t\t\t\t\xB3\xB3                                                          \t\xB3\xB3");
	printf(BLUE "\n\t\t\t\t\xB3\xB3                                                          \t\xB3\xB3");
	printf(BLUE "\n\t\t\t\t\xB3\xB3                                                          \t\xB3\xB3");
	printf(BLUE "\n\t\t\t\t\xB3\xB3                                                          \t\xB3\xB3");
	printf(BLUE "\n\t\t\t\t\xB3\xB3                                                          \t\xB3\xB3");
	printf(CYAN "\n\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf(CYAN "\n\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf(CYAN "\n\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf(CYAN "\n\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2"BLUE);
	
	cout<<'\n';
	system("pause");
	getch();
	clrscr();
	
	system("COLOR 3F");
}

int main(){
	Electionday E;
	User_Interface::displaymain();
	E.main_page();
	
}


