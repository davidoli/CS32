//
//  eval.cpp
//  Homework 2
//
//  Created by David Li on 2/3/17.
//  Copyright © 2017 cs32. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <stack>
#include <cassert>

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

using namespace std;



bool valid(string infix); // Checks if infix is valid
int precedence(char ch); // Assumes valid, and evaluates the precedence of !, & and |
string convert(string infix, string& postfix); // Assumes valid and converts from infix to postfix



int evaluate(string infix, const bool values[], string& postfix, bool& result){
    if(valid(infix)){
        stack<bool> operandStack;
        
        postfix = convert(infix, postfix);
        
        if (postfix.empty())
            return 1;
        
        for(int i = 0; i<postfix.size(); i++){        //deal with numbers!
            char ch = postfix[i];
            if (ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9'){
                int int_ch = ch-'0';
                operandStack.push(values[int_ch]);
            }
            else if (ch == '!'){
                bool x = operandStack.top();
                operandStack.pop();
                operandStack.push(!x);
            }
            else{                                           //deal with | and &
                bool operand2 = operandStack.top();
                operandStack.pop();
                
                if(operandStack.empty())
                    return 1;
                
                bool operand1 = operandStack.top();
                operandStack.pop();
                if(postfix[i] == '|'){
                    if(operand1 || operand2)
                        operandStack.push(true);
                    else
                        operandStack.push(false);
                }
                if(postfix[i] == '&'){
                    if(operand1 && operand2)
                        operandStack.push(true);
                    else
                        operandStack.push(false);
                }
            }
        }
        result = operandStack.top();
        return 0;
    }
    
    return 1;
}


string convert(string infix, string& postfix){
    postfix = "";
    stack<char> operatorStack;
    for (int i = 0; i < infix.size(); i++){
        char ch = infix[i];
        switch (ch){
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                postfix += ch;
                break;
            case '(':
                operatorStack.push(ch);
                break;
            case ')':
                while (operatorStack.top() != '('){
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.pop();
                break;
            case '&':
            case '|':
            case '!':
                while (!operatorStack.empty() && operatorStack.top() != '(' && precedence(ch) <= precedence(operatorStack.top())){                                                        //precedence??
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.push(ch);
                break;
                
            default:
                break;
        }
    }
    while(!operatorStack.empty()){
        postfix += operatorStack.top();
        operatorStack.pop();
    }
    return postfix;
}

int precedence(char c){
    if (c == '!')
        return 3;
    if (c == '&')
        return 2;
    if (c == '|')
        return 1;
    else
        return 0;
}

bool valid(string infix){
    
    string infix_nospace = "";                             //make sure there's no spaces in infix
    for(int i = 0; i<infix.size(); i++){
        if(infix[i] != ' ')
            infix_nospace += infix[i];
    }
    
    for(int i=0; i<infix_nospace.size();i++){                 //loop through infix
        if(infix_nospace.size()-1 == '|' || infix_nospace.size()-1 == '&' || infix_nospace.size()-1 == '(')     //if last value is |, (, or &, not valid.
            return false;
        
        if(isdigit(infix_nospace[i])){                         //if number, can't have number, !, or ( after it.
            if(isdigit(infix_nospace[i+1])||infix_nospace[i+1] == '!'||infix_nospace[i+1] == '(')
                return false;
        }
        else if (infix_nospace[i] == '|' || infix_nospace[i] == '&'){
            
                                                    //if | or &, can only have T, F, or ) before, and T, F, !, or ( after.
            if((!isdigit(infix_nospace[i-1]) && infix_nospace[i-1] != ')') || (!isdigit(infix_nospace[i+1]) && infix_nospace[i+1] != '!' && infix_nospace[i+1] != '(')){
                return false;
            }
        }
    }
    return true;
}

int main()
{
    bool ba[10] = {
        //  0      1      2      3      4      5      6      7      8      9
        true,  true,  true,  false, false, false, true,  false, true,  false
    };
    string pf;
    bool answer;
    
    assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  answer);
    assert(evaluate("8|", ba, pf, answer) == 1);
    assert(evaluate("4 5", ba, pf, answer) == 1);
    assert(evaluate("01", ba, pf, answer) == 1);
    assert(evaluate("()", ba, pf, answer) == 1);
    assert(evaluate("2(9|8)", ba, pf, answer) == 1);
    assert(evaluate("2(&8)", ba, pf, answer) == 1);
    assert(evaluate("(6&(7|7)", ba, pf, answer) == 1);
    assert(evaluate("", ba, pf, answer) == 1);
    assert(evaluate("4  |  !3 & (0&3) ", ba, pf, answer) == 0
          &&  pf == "43!03&&|"  &&  !answer);
    assert(evaluate(" 9  ", ba, pf, answer) == 0  &&  pf == "9"  &&  !answer);
    
    ba[2] = false;
    ba[9] = true;
    
    assert(evaluate("((9)", ba, pf, answer) == 0  &&  pf == "9"  &&  answer);
    assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  !answer);
    cout << "Passed all tests" << endl;
}
