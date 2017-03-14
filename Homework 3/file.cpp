//
//  file.cpp
//  Homework 3
//
//  Created by David Li on 2/8/17.
//  Copyright © 2017 cs32. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

class File {

public:
    File(string name_me)
        {file_name = name_me;}
    virtual ~File(){};
    string name() const                 //is this also abstract?
        {return file_name;}
    virtual void open() const = 0;
    virtual void redisplay() const = 0;
    
private:
    string file_name;
    
};
/////       Text Msg      //////////
class TextMsg: public File{
public:
    TextMsg(string name_me) : File(name_me) {}
    virtual ~TextMsg(){
        cout << "Destroying " << this->name() << ", a text message" << endl;
        //delete this;
    }
    virtual void open() const{
        cout << "open text message";
    }
    virtual void redisplay() const{
        cout << "refresh the screen";
    }
};
//////////   Video       ///////////
class Video: public File{
public:
    Video(string name_me, int x) : File(name_me)
    {runtime = x;}
    virtual ~Video(){
        cout << "Destroying " << this->name() << ", a video" << endl;
       // delete this;
    }
    virtual void open() const{
        cout << "play " << runtime << " second video";
    }
    virtual void redisplay() const{
        cout << "replay the video";
    }
private:
    int runtime;
};
/////////   Picture      /////////
class Picture: public File{
public:
    Picture(string name_me) : File(name_me) {}
    virtual ~Picture(){
        cout << "Destroying the picture " << this->name() << endl;
      //  delete this;
    }
    virtual void open() const{
        cout << "show picture";
    }
    virtual void redisplay() const{
        cout << "refresh the screen";
    }
};

void openAndRedisplay(const File* f)
{
    cout << f->name() << ": ";
    f->open();
    cout << endl << "Redisplay: ";
    f->redisplay();
    cout << endl;
}
/*
int main()
{
    File* files[4];
    files[0] = new TextMsg("fromFred.txt");
    // Videos have a name and running time
    files[1] = new Video("goblin.mpg", 3780);
    files[2] = new Picture("kitten.jpg");
    files[3] = new Picture("baby.jpg");
    
    for (int k = 0; k < 4; k++)
        openAndRedisplay(files[k]);
    
    // Clean up the files before exiting
    cout << "Cleaning up." << endl;
    for (int k = 0; k < 4; k++)
        delete files[k];
}
*/
