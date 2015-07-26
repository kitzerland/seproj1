#ifndef FORMULATOR_H
#define FORMULATOR_H

#include <iostream>
#include <vector>
#include <math.h>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <cstring>
using namespace std;

//package Formulator
namespace Formulator {

//parent class FormulaElement
class FormulaElement {

public:
    bool isConstant; //to keep track of the instance, if it is of the base class ConstantElement
    bool isVariable; //to keep track of the instance, if it is of the base class VariableElement
    bool isOperator; //to keep track of the instance, if it is of the base class FunctionElement

    virtual double get() {
        return 0;
    }
    virtual string toString() {
        return "";
    }
    static FormulaElement* parseFormula(string); //implemented below classes

    virtual void setVariableValue(string varName, double value) {
        //redefined in sub classes
    }
    virtual bool isFullyGrounded() {
        return true;
        //redefined in sub classes
    }
    virtual double evaluate() {
        return 0;
    }

    static void printTockens(vector<string>, vector<FormulaElement*>); //this method is created for testing purposes only

    static double isDouble(const std::string & s) {
        if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
            return false;

        char * p;
        strtof(s.c_str(), &p);
        return (*p == 0);
    }
    static vector<string> createTockens(string text) { //strtok(string, delemeters) does not return split elements including delimiters. so i had to create a custom method
        text.erase(remove(text.begin(), text.end(), ' '), text.end()); //removing spaces
        text.erase(remove(text.begin(), text.end(), '\t'), text.end()); //removing tabs

        vector<string> partialTockens;
        for (unsigned int i = 0; i < text.length(); i++) {
            stringstream holderss;
            string charset = "";
            charset = text[i];
            if (text[i] == 's' || text[i] == 'c' || text[i] == 't' || text[i] == 'l' || text[i] == 'p') {
                if (i + 2 < text.length()) {
                    stringstream ss;
                    string s;
                    ss << text[i] << text[i + 1] << text[i + 2];
                    ss >> s;
                    if (s == "sin" || s == "cos" || s == "tan" || s == "log") {
                        charset = s;
                        i = i + 2;
                    }
                }
                if (i + 1 < text.length()) {
                    stringstream ss;
                    string s;
                    ss << text[i] << text[i + 1];
                    ss >> s;
                    if (s == "pi") {
                        charset = s;
                        i = i + 1;
                    }
                }
            }
            partialTockens.push_back(charset);
        }

        vector<string> tockens;
        for (unsigned int i = 0; i < partialTockens.size(); i++) {
            stringstream ll;
            string l = "";
            string r = "";
            for (unsigned int j = i; j < partialTockens.size(); j++) {
                if (isDouble(partialTockens.at(j))) {
                    ll << partialTockens.at(j);
                    i = j;
                } else {
                    i = j;
                    r = partialTockens.at(i);
                    break;
                }
            }
            ll >> l;
            if (l != "") {
                tockens.push_back(l);
            }
            if (r != "") {
                tockens.push_back(r);
            }
        }
        return tockens;

    }
    static bool isConstantORVariable(string text) {
        if (text == "sin") {
            return false;
        } else if (text == "cos") {
            return false;
        } else if (text == "tan") {
            return false;
        } else if (text == "log") {
            return false;
        } else if (text == "pi") {
            return false;
        } else if (text == "!") {
            return false;
        } else if (text == "+") {
            return false;
        } else if (text == "-") {
            return false;
        } else if (text == "/") {
            return false;
        } else if (text == "*") {
            return false;
        } else if (text == "x") {
            return false;
        } else if (text == "^") {
            return false;
        } else if (text == "%") {
            return false;
        } else if (text == "(") {
            return false;
        } else if (text == ")") {
            return false;
        } else if (isDouble(text)) {
            return true;
        } else if (text == "0") {
            return true;
        } else {
            return true;
        }
    }
    static string tockenType(string text) {
        if (text == "sin") {
            return "sin";
        } else if (text == "cos") {
            return "cos";
        } else if (text == "tan") {
            return "tan";
        } else if (text == "log") {
            return "log";
        } else if (text == "pi") {
            return "pi";
        } else if (text == "!") {
            return "factorial";
        } else if (text == "+") {
            return "plus";
        } else if (text == "-") {
            return "minus";
        } else if (text == "/") {
            return "divide";
        } else if (text == "*") {
            return "multiply";
        } else if (text == "x") {
            return "multiply";
        } else if (text == "^") {
            return "power";
        } else if (text == "%") {
            return "modulus";
        } else if (text == "(") {
            return "lbracket";
        } else if (text == ")") {
            return "rbracket";
        } else if (isDouble(text)) {
            return "constant";
        } else if (text == "0") {
            return "constant";
        } else {
            return "variable";
        }
    }
    virtual ~FormulaElement() {
    }
};

//child class ConstantElement of parent FormulaElement
class ConstantElement: public FormulaElement {
private:
    double constant;

public:
    ConstantElement(double c) {
        isConstant = 1;
        isVariable = 0;
        isOperator = 0;
        constant = c;
    }
    double get() {
        return constant;
    }
    string toString() {
        stringstream stream;
        string str;
        stream << this->constant;
        stream >> str;
//		cout << str << endl;
        return str;
    }

    void setVariableValue(string varName, double value) {
        //nothing to implement
    }
    bool isFullyGrounded() {
        return true;
    }
    double evaluate() {
        return this->get();
    }
};

//child class VariableElement of parent FormulaElement
class VariableElement: public FormulaElement {
private:
    string variableName;
    double variableValue;
    bool grounded;
public:
    VariableElement(string name) {
        grounded = false;
        isVariable = 1;
        isConstant = 0;
        isOperator = 0;
        this->variableName = name;
        this->variableValue = 0.0;
    }
    string getName() {
        return variableName;
    }
    double getValue() {
        return this->variableValue;
    }
    void setValue(double v) {
        this->variableValue = v;
    }
    string toString() {
//		cout << variableName << endl;
        return this->variableName;
    }
    void setVariableValue(string varName, double value) {
        if (this->getName() == varName) {
            this->setValue(value);
            this->grounded = true;
        }
    }
    bool isFullyGrounded() {
        return grounded;
    }
    double evaluate() {
        return this->getValue();
    }
};

//child class FunctionElement of parent FormulaElement
class FunctionElement: public FormulaElement {
private:

    vector<FormulaElement*> arguments;
public:
    void addArgument(FormulaElement* argument) {
        arguments.push_back(argument);
    }

    vector<FormulaElement*> getArguments() {
        return arguments;
    }
    string toString() {
        return NULL;
    }

    void setVariableValue(string varName, double value) {
        for (unsigned int i = 0; i < arguments.size(); i++) {
            arguments.at(i)->setVariableValue(varName, value);
        }
    }
    bool isFullyGrounded() {
        for (unsigned int i = 0; i < arguments.size(); i++) {
            if (!arguments.at(i)->isFullyGrounded()) {
                return false;
            }
        }
        return true;
    }
};

class FactorialFunctionElement: public FunctionElement {
    FunctionElement fe;
public:
    FactorialFunctionElement(FunctionElement arguments) {
        fe = arguments;
        isOperator = 1;
        isConstant = 0;
        isVariable = 0;
    }

    double getFactorial(double n) {
        if (n <= 1)
            return 1;
        else
            return n * getFactorial(n - 1);
    }

    string toString() {
        stringstream stream;
        string str;

        FormulaElement *arg = fe.getArguments().at(0);

        if (arg->isOperator) {
            string s = arg->toString();
            double n = atof(s.c_str()); //returns 0 if it is not a double

            if (s == "0") { //argument can be 0
                stream << getFactorial(n);
            } else {
                if (isDouble(s)) { //argument can be a double value
                    stream << getFactorial(n);
                } else { //or it can be a string
                    if (s.find("(") != string::npos && s.find("(") == 0) { // if argument already contains one '(' parentheses in the FRONT, there is no need to put them again
                        stream << s << "!";
                    } else {
                        stream << s << "!";
                    }
                }
            }
        } else {
            if (arg->isConstant) {
                stream << getFactorial(arg->get());
            } else {
                stream << arg->toString() << "!";
            }
        }

        stream >> str;
        //		cout << str << endl << endl;
        return str;
    }

    void setVariableValue(string varName, double value) {
        for (unsigned int i = 0; i < fe.getArguments().size(); i++) {
            fe.getArguments().at(i)->setVariableValue(varName, value);
        }
    }

    bool isFullyGrounded() {
        for (unsigned int i = 0; i < fe.getArguments().size(); i++) {
            if (!fe.getArguments().at(i)->isFullyGrounded()) {
                return false;
            }
        }
        return true;
    }

    double evaluate() {
        return getFactorial(fe.getArguments().at(0)->evaluate());
    }

};

//child class PlusFunctionElement of parent FunctionElement
class PlusFunctionElement: public FunctionElement {
    FunctionElement fe;
public:
    PlusFunctionElement(FunctionElement arguments) {
        fe = arguments;
        isOperator = 1;
        isConstant = 0;
        isVariable = 0;
    }
    string toString() {
        stringstream stream;
        string str;

        FormulaElement *leftArg = fe.getArguments().at(0);
        FormulaElement *rightArg = fe.getArguments().at(1);

        string ls = leftArg->toString();
        string rs = rightArg->toString();
        double ln = atof(ls.c_str()); //returns 0 if it is not a double
        double rn = atof(rs.c_str());

        if (leftArg->isOperator || rightArg->isOperator) {

            if (ls == "0" || rs == "0") {
                if (ls == "0") {
                    stream << rs;
                } else {
                    stream << ls;
                }
            } else {
                if (isDouble(ls) && isDouble(rs)) { //left and right parameter can be double values
                    stream << ln + rn; //so numbers should be computed to get the result
                } else { //one or both can be a string
                    stream << "(" << ls << "+" << rs << ")";
                }
            }

        } else {
            if (leftArg->isConstant && rightArg->isConstant) {
                stream << leftArg->get() + rightArg->get();
            } else {
                stream << "(" << leftArg->toString() << "+" << rightArg->toString() << ")";
            }
        }

        stream >> str;
//		cout << str << endl << endl;
        return str;
    }

    void setVariableValue(string varName, double value) {
        for (unsigned int i = 0; i < fe.getArguments().size(); i++) {
            fe.getArguments().at(i)->setVariableValue(varName, value);
        }
    }

    bool isFullyGrounded() {
        for (unsigned int i = 0; i < fe.getArguments().size(); i++) {
            if (!fe.getArguments().at(i)->isFullyGrounded()) {
                return false;
            }
        }
        return true;
    }

    double evaluate() {
        return fe.getArguments().at(0)->evaluate() + fe.getArguments().at(1)->evaluate();
    }

};

//child class MinusFunctionElement of parent FunctionElement
class MinusFunctionElement: public FunctionElement {
    FunctionElement fe;
public:
    MinusFunctionElement(FunctionElement arguments) {
        isOperator = 1;
        isConstant = 0;
        isVariable = 0;
        fe = arguments;
    }
    string toString() {
        stringstream stream;
        string str;

        FormulaElement *leftArg = fe.getArguments().at(0);
        FormulaElement *rightArg = fe.getArguments().at(1);

        if (leftArg->isOperator || rightArg->isOperator) {

            string ls = leftArg->toString();
            string rs = rightArg->toString();
            double ln = atof(ls.c_str()); //returns 0 if it is not a double
            double rn = atof(rs.c_str());

            if (ls == "0" || rs == "0") { //anything multiplied by 0 should be 0
                if (ls == "0") {
                    stream << rs;
                } else {
                    stream << ls;
                }
            } else {
                if (isDouble(ls) && isDouble(rs)) { //left and right parameter can be a double
                    stream << ln - rn; //so numbers should be computed to get the result
                } else { //one or both can be a string
                    stream << "(" << ls << "-" << rs << ")";
                }
            }

        } else {
            if (leftArg->isConstant && rightArg->isConstant) {
                stream << leftArg->get() - rightArg->get();
            } else {
                stream << "(" << leftArg->toString() << "-" << rightArg->toString() << ")";
            }
        }

        stream >> str;
//		cout << str << endl << endl;
        return str;
    }

    void setVariableValue(string varName, double value) {
        for (unsigned int i = 0; i < fe.getArguments().size(); i++) {
            fe.getArguments().at(i)->setVariableValue(varName, value);
        }
    }

    bool isFullyGrounded() {
        for (unsigned int i = 0; i < fe.getArguments().size(); i++) {
            if (!fe.getArguments().at(i)->isFullyGrounded()) {
                return false;
            }
        }
        return true;
    }

    double evaluate() {
        return fe.getArguments().at(0)->evaluate() - fe.getArguments().at(1)->evaluate();
    }
};

//child class MultipleFunctionElement of parent FunctionElement
class MultipleFunctionElement: public FunctionElement {
    FunctionElement fe;
public:
    MultipleFunctionElement(FunctionElement arguments) {
        isOperator = 1;
        isConstant = 0;
        isVariable = 0;
        fe = arguments;
    }
    string toString() {
        stringstream stream;
        string str;

        FormulaElement *leftArg = fe.getArguments().at(0);
        FormulaElement *rightArg = fe.getArguments().at(1);

        string ls = leftArg->toString();
        string rs = rightArg->toString();
        double ln = atof(ls.c_str()); //returns 0 if it is not a double
        double rn = atof(rs.c_str());

        if (leftArg->isOperator || rightArg->isOperator) {

            if (ls == "0" || rs == "0") { //anything multiplied by 0 should be 0
                stream << 0;
            } else {
                if (isDouble(ls) && isDouble(rs)) { //left and right parameter can be a double value
                    stream << ln * rn; //so numbers should be computed to get the result
                } else { //one or both can be a string
                    stream << ls << rs;
                }
            }
        } else {
            if (leftArg->isConstant && rightArg->isConstant) { //left and right parameters can be constants
                stream << leftArg->get() * rightArg->get(); //so they should be multiplied to get the result
            } else {
                if (ls == "0" || rs == "0") { //anything multiplied by 0 should be 0
                    stream << 0;
                } else {
                    if (leftArg->isConstant || rightArg->isConstant) {
                        if (leftArg->isConstant) { //it should be 2X but never X2
                            stream << leftArg->toString() << rightArg->toString();
                        } else {
                            stream << rightArg->toString() << leftArg->toString();
                        }
                    } else {
                        stream << leftArg->toString() << rightArg->toString();
                    }
                }
            }
        }

        stream >> str;
//		cout << str << endl << endl;
        return str;
    }

    void setVariableValue(string varName, double value) {
        for (unsigned int i = 0; i < fe.getArguments().size(); i++) {
            fe.getArguments().at(i)->setVariableValue(varName, value);
        }
    }

    bool isFullyGrounded() {
        for (unsigned int i = 0; i < fe.getArguments().size(); i++) {
            if (!fe.getArguments().at(i)->isFullyGrounded()) {
                return false;
            }
        }
        return true;
    }

    double evaluate() {
        return fe.getArguments().at(0)->evaluate() * fe.getArguments().at(1)->evaluate();
    }
};

//child class DivideFunctionElement of parent FunctionElement
class DivideFunctionElement: public FunctionElement {
    FunctionElement fe;
public:
    DivideFunctionElement(FunctionElement arguments) {
        isOperator = 1;
        isConstant = 0;
        isVariable = 0;
        fe = arguments;
    }
    string toString() {
        stringstream stream;
        string str;

        FormulaElement *leftArg = fe.getArguments().at(0);
        FormulaElement *rightArg = fe.getArguments().at(1);
        string ls = leftArg->toString();
        string rs = rightArg->toString();
        double ln = atof(ls.c_str()); //returns 0 if it is not a double
        double rn = atof(rs.c_str());

        if (leftArg->isOperator || rightArg->isOperator) {

            if (ls == "0") { //0 divided by anything should be 0
                stream << 0;
            } else {

                if (isDouble(ls) && isDouble(rs)) { //left and right parameter can be a double value

                    stream << ln / rn; //so numbers should be computed to get the result
                } else { //one or both can be a string
                    stream << ls << "/" << rs;
                }
            }
        } else {
            if (leftArg->isConstant && rightArg->isConstant) {
                stream << leftArg->get() / rightArg->get();
            } else {
                stream << leftArg->toString() << "/" << rightArg->toString();
            }
            cout << "divide ls " << ls << endl;
            cout << "divide rs " << rs << endl;
        }

        stream >> str;
//		cout << " devide str " << str << endl << endl;
        return str;
    }

    void setVariableValue(string varName, double value) {
        for (unsigned int i = 0; i < fe.getArguments().size(); i++) {
            fe.getArguments().at(i)->setVariableValue(varName, value);
        }
    }

    bool isFullyGrounded() {
        for (unsigned int i = 0; i < fe.getArguments().size(); i++) {
            if (!fe.getArguments().at(i)->isFullyGrounded()) {
                return false;
            }
        }
        return true;
    }

    double evaluate() {
        return fe.getArguments().at(0)->evaluate() / fe.getArguments().at(1)->evaluate();
    }
};

//child class CosineFunctionElement of parent FunctionElement
class CosineFunctionElement: public FunctionElement {
    FunctionElement fe;
public:
    CosineFunctionElement(FunctionElement argument) {
        isOperator = 1;
        isConstant = 0;
        isVariable = 0;
        fe = argument;
    }
    string toString() {
        stringstream stream;
        string str;

        FormulaElement *arg = fe.getArguments().at(0);

        if (arg->isOperator) {
            string s = arg->toString();
            double n = atof(s.c_str()); //returns 0 if it is not a double

            if (s == "0") { //argument can be 0
                stream << cos(n);
            } else {
                if (isDouble(s)) { //argument can be a double value
                    stream << cos(n);
                } else { //or it can be a string
                    if (s.find("(") != string::npos && s.find("(") == 0) { // if argument already contains one '(' parentheses in the FRONT, there is no need to put them again
                        stream << "cos" << s;
                    } else {
                        stream << "cos(" << s << ")";
                    }
                }
            }
        } else {
            if (arg->isConstant) {
                stream << cos(arg->get());
            } else {
                stream << "cos(" << arg->toString() << ")";
            }
        }

        stream >> str;
//		cout << str << endl << endl;
        return str;
    }

    void setVariableValue(string varName, double value) {
        for (unsigned int i = 0; i < fe.getArguments().size(); i++) {
            fe.getArguments().at(i)->setVariableValue(varName, value);
        }
    }

    bool isFullyGrounded() {
        for (unsigned int i = 0; i < fe.getArguments().size(); i++) {
            if (!fe.getArguments().at(i)->isFullyGrounded()) {
                return false;
            }
        }
        return true;
    }

    double evaluate() {
        return cos(fe.getArguments().at(0)->evaluate());
    }
};

//child class SineFunctionElement of parent FunctionElement
class SineFunctionElement: public FunctionElement {
    FunctionElement fe;
public:
    SineFunctionElement(FunctionElement argument) {
        isOperator = 1;
        isConstant = 0;
        isVariable = 0;
        fe = argument;
    }
    string toString() {
        stringstream stream;
        string str;

        FormulaElement *arg = fe.getArguments().at(0);

        if (arg->isOperator) {

            string s = arg->toString();
            double n = atof(s.c_str()); //returns 0 if it is not a double

            if (s == "0") { //argument can be 0
                stream << sin(n);
            } else {
                if (isDouble(s)) { //argument can be a double
                    stream << sin(n);
                } else { //or it can be a string
                    if (s.find("(") != string::npos && s.find("(") == 0) { // if argument contains one '(' parentheses in the FRONT, there is no need to put them again
                        stream << "sin" << s;
                    } else {
                        stream << "sin(" << s << ")";
                    }
                }
            }

        } else {
            if (arg->isConstant) {
                stream << sin(arg->get());
            } else {
                stream << "sin(" << arg->toString() << ")";
            }
        }

        stream >> str;
//		cout << str << endl << endl;
        return str;
    }

    void setVariableValue(string varName, double value) {
        for (unsigned int i = 0; i < fe.getArguments().size(); i++) {
            fe.getArguments().at(i)->setVariableValue(varName, value);
        }
    }

    bool isFullyGrounded() {
        for (unsigned int i = 0; i < fe.getArguments().size(); i++) {
            if (!fe.getArguments().at(i)->isFullyGrounded()) {
                return false;
            }
        }
        return true;
    }

    double evaluate() {
        return sin(fe.getArguments().at(0)->evaluate());
    }
};

class TanFunctionElement: public FunctionElement {
    FunctionElement fe;
public:
    TanFunctionElement(FunctionElement argument) {
        isOperator = 1;
        isConstant = 0;
        isVariable = 0;
        fe = argument;
    }
    string toString() {
        stringstream stream;
        string str;

        FormulaElement *arg = fe.getArguments().at(0);

        if (arg->isOperator) {

            string s = arg->toString();
            double n = atof(s.c_str()); //returns 0 if it is not a double

            if (s == "0") { //argument can be 0
                stream << tan(n);
            } else {
                if (isDouble(s)) { //argument can be a double
                    stream << tan(n);
                } else { //or it can be a string
                    if (s.find("(") != string::npos && s.find("(") == 0) { // if argument contains one '(' parentheses in the FRONT, there is no need to put them again
                        stream << "tan" << s << "";
                    } else {
                        stream << "tan(" << s << ")";
                    }
                }
            }

        } else {
            if (arg->isConstant) {
                stream << tan(arg->get());
            } else {
                stream << "tan(" << arg->toString() << ")";
            }
        }

        stream >> str;
//		cout << str << endl << endl;
        return str;
    }

    void setVariableValue(string varName, double value) {
        for (unsigned int i = 0; i < fe.getArguments().size(); i++) {
            fe.getArguments().at(i)->setVariableValue(varName, value);
        }
    }

    bool isFullyGrounded() {
        for (unsigned int i = 0; i < fe.getArguments().size(); i++) {
            if (!fe.getArguments().at(i)->isFullyGrounded()) {
                return false;
            }
        }
        return true;
    }

    double evaluate() {
        return tan(fe.getArguments().at(0)->evaluate());
    }
};

class LogFunctionElement: public FunctionElement {
    FunctionElement fe;
public:
    LogFunctionElement(FunctionElement argument) {
        isOperator = 1;
        isConstant = 0;
        isVariable = 0;
        fe = argument;
    }
    string toString() {
        stringstream stream;
        string str;

        FormulaElement *arg = fe.getArguments().at(0);

        if (arg->isOperator) {

            string s = arg->toString();
            double n = atof(s.c_str()); //returns 0 if it is not a double

            if (s == "0") { //argument can be 0
                stream << log10(n);
            } else {
                if (isDouble(s)) { //argument can be a double
                    stream << log10(n);
                } else { //or it can be a string
                    if (s.find("(") != string::npos && s.find("(") == 0) { // if argument contains one '(' parentheses in the FRONT, there is no need to put them again
                        stream << "log" << s << "";
                    } else {
                        stream << "log(" << s << ")";
                    }
                }
            }

        } else {
            if (arg->isConstant) {
                stream << log10(arg->get());
            } else {
                stream << "log(" << arg->toString() << ")";
            }
        }

        stream >> str;
//		cout << str << endl << endl;
        return str;
    }

    void setVariableValue(string varName, double value) {
        for (unsigned int i = 0; i < fe.getArguments().size(); i++) {
            fe.getArguments().at(i)->setVariableValue(varName, value);
        }
    }

    bool isFullyGrounded() {
        for (unsigned int i = 0; i < fe.getArguments().size(); i++) {
            if (!fe.getArguments().at(i)->isFullyGrounded()) {
                return false;
            }
        }
        return true;
    }

    double evaluate() {
        return log10(fe.getArguments().at(0)->evaluate());
    }
};

class PowerFunctionElement: public FunctionElement {
    FunctionElement fe;
public:
    PowerFunctionElement(FunctionElement arguments) {
        isOperator = 1;
        isConstant = 0;
        isVariable = 0;
        fe = arguments;
    }
    string toString() {

        stringstream stream;
        string str;

        FormulaElement *leftArg = fe.getArguments().at(0);
        FormulaElement *rightArg = fe.getArguments().at(1);

        string ls = leftArg->toString();
        string rs = rightArg->toString();
        double ln = atof(ls.c_str()); //returns 0 if it is not a double
        double rn = atof(rs.c_str());

        if (leftArg->isOperator || rightArg->isOperator) {

            if (ls == "0" || rs == "0") {
                if (rs == "0") { //anything to the power 0 is 1
                    stream << 1;
                } else {
                    stream << 0; //0 to the power anything except 0 is 0
                }
            } else {

                if (isDouble(ls) && isDouble(rs)) { // both can be a double
                    stream << pow(ln, rn); //so numbers should be computed to get the result
                } else { //one or both can be a string
                    stream << ls << "^" << rs;
                }
            }

        } else {
            if (leftArg->isConstant && rightArg->isConstant) {
                stream << pow(leftArg->get(), rightArg->get());
            } else {
                if (ls == "0" || rs == "0") {
                    if (rs == "0") { //anything to the power 0 is 1
                        stream << 1;
                    } else {
                        stream << 0; //0 to the power anything except 0 is 0
                    }
                } else {
                    stream << leftArg->toString() << "^" << rightArg->toString();
                }
            }
        }

        stream >> str;
        //		cout << str << endl << endl;
        return str;
    }

    void setVariableValue(string varName, double value) {
        for (unsigned int i = 0; i < fe.getArguments().size(); i++) {
            fe.getArguments().at(i)->setVariableValue(varName, value);
        }
    }

    bool isFullyGrounded() {
        for (unsigned int i = 0; i < fe.getArguments().size(); i++) {
            if (!fe.getArguments().at(i)->isFullyGrounded()) {
                return false;
            }
        }
        return true;
    }

    double evaluate() {
        return pow(fe.getArguments().at(0)->evaluate(), fe.getArguments().at(1)->evaluate());
    }
};

class ModulusFunctionElement: public FunctionElement {
    FunctionElement fe;
public:
    ModulusFunctionElement(FunctionElement arguments) {
        isOperator = 1;
        isConstant = 0;
        isVariable = 0;
        fe = arguments;
    }
    string toString() {

        stringstream stream;
        string str;

        FormulaElement *leftArg = fe.getArguments().at(0);
        FormulaElement *rightArg = fe.getArguments().at(1);

        string ls = leftArg->toString();
        string rs = rightArg->toString();
        double ln = atof(ls.c_str()); //returns 0 if it is not a double
        double rn = atof(rs.c_str());

        if (leftArg->isOperator || rightArg->isOperator) {

            if (ls == "0" || rs == "0") {
                stream << 0;
            } else {
                if (isDouble(ls) && isDouble(rs)) { // both can be a double
                    stream << (ln * rn) / 100; //so numbers should be computed to get the result
                } else { //one or both can be a string
                    stream << rn << "%";
                }
            }
        } else {
            if (leftArg->isConstant && rightArg->isConstant) {
                stream << (leftArg->get() * rightArg->get()) / 100;
            } else {
                if (ls == "0" || rs == "0") {
                    stream << 0;
                } else {
                    stream << rightArg->toString() << "%";
                }
            }
        }

        stream >> str;
        //		cout << str << endl << endl;
        return str;
    }

    void setVariableValue(string varName, double value) {
        for (unsigned int i = 0; i < fe.getArguments().size(); i++) {
            fe.getArguments().at(i)->setVariableValue(varName, value);
        }
    }

    bool isFullyGrounded() {
        for (unsigned int i = 0; i < fe.getArguments().size(); i++) {
            if (!fe.getArguments().at(i)->isFullyGrounded()) {
                return false;
            }
        }
        return true;
    }
    double evaluate() {
        return fe.getArguments().at(0)->evaluate() * fe.getArguments().at(1)->evaluate() / 100;
    }
};

class PiFunctionElement: public FunctionElement {

public:
    PiFunctionElement() {
        isOperator = 1; //this must be categorized as an operator because there is no get method implemented inside this class
        isConstant = 0;
        isVariable = 0;
    }
    string toString() {
        stringstream stream;
        string str;
        stream << M_PI;
        stream >> str;
        return str;
    }

    void setVariableValue(string varName, double value) {
        //nothing to implement
    }
    bool isFullyGrounded() {
        return true;
    }
    double evaluate() {
        return M_PI;
    }
};

FormulaElement* FormulaElement::parseFormula(string text) {
    vector<string> tockens = createTockens(text);

//	cout << endl << endl;
//	for (unsigned int i = 0; i < tockens.size(); i++) {
//		cout << tockens.at(i) << endl;
//	}
//	cout << endl;

    vector<FormulaElement*> transformedVector(tockens.size());

    //pass one //constants and variables
    for (unsigned int i = 0; i < tockens.size(); i++) {
        if (tockenType(tockens.at(i)) == "constant") {
            double n = atof(tockens.at(i).c_str());
            ConstantElement *ce = new ConstantElement(n);
            transformedVector.at(i) = ce;
        }
        if (tockenType(tockens.at(i)) == "variable") {
            VariableElement *ve = new VariableElement(tockens.at(i));
            transformedVector.at(i) = ve;
        }
    }

    for (unsigned int i = 0; i < tockens.size(); i++) {
        if (tockenType(tockens.at(i)) == "pi") {
            PiFunctionElement *pi = new PiFunctionElement();
            transformedVector.at(i) = pi;
        }
    }

//	printTockens(tockens, transformedVector);

    //pass two //MultipleFunctionElement for Compound elements
    for (unsigned int i = 0; i < tockens.size(); i++) {
        if (i + 1 < tockens.size()) {
            if (isConstantORVariable(tockens.at(i)) && isConstantORVariable(tockens.at(i + 1))) {
                FunctionElement fe;
                fe.addArgument(transformedVector.at(i));
                fe.addArgument(transformedVector.at(i + 1));
                MultipleFunctionElement *me = new MultipleFunctionElement(fe);
                transformedVector.at(i) = me;

                transformedVector.erase(transformedVector.begin() + i + 1);
                tockens.erase(tockens.begin() + i + 1);
            }
        }
    }

    for (unsigned int formulaElements = 0; formulaElements < tockens.size();
            formulaElements++) { //recursively iterating the process until the formula is fully parsed

        for (unsigned int i = 0; i < tockens.size(); i++) {
            if (tockenType(tockens.at(i)) == "factorial") {

                if ((int) (i - 1) >= 0 && i < transformedVector.size()) {
                    if (transformedVector.at(i - 1) != NULL) {
                        FunctionElement fe;
                        fe.addArgument(transformedVector.at(i - 1));

                        FactorialFunctionElement *fct = new FactorialFunctionElement(fe);
                        transformedVector.at(i - 1) = fct;

                        transformedVector.erase(transformedVector.begin() + i); // removing operator
                        tockens.erase(tockens.begin() + i);
                    }
                }
            }
        }

        //pass four //powerFunctionElement
        for (unsigned int i = 0; i < tockens.size(); i++) {
            if (tockenType(tockens.at(i)) == "power") {

                if ((int) (i - 1) >= 0 && i + 1 < transformedVector.size()) {
                    if (transformedVector.at(i - 1) != NULL && transformedVector.at(i + 1) != NULL) {
                        FunctionElement fe;
                        fe.addArgument(transformedVector.at(i - 1));
                        fe.addArgument(transformedVector.at(i + 1));

                        PowerFunctionElement *pe = new PowerFunctionElement(fe);
                        transformedVector.at(i - 1) = pe;

                        transformedVector.erase(transformedVector.begin() + i); // removing operator
                        tockens.erase(tockens.begin() + i);

                        transformedVector.erase(transformedVector.begin() + i); // removing element
                        tockens.erase(tockens.begin() + i);
                    }
                }
            }
        }

        for (unsigned int i = 0; i < tockens.size(); i++) {
            if (tockenType(tockens.at(i)) == "modulus") {
                // 72+5%
                if ((int) (i - 3) >= 0 && i < transformedVector.size()) {
                    if (transformedVector.at(i - 1) != NULL && transformedVector.at(i - 3) != NULL && !isConstantORVariable(tockens.at(i - 2))) {
                        FunctionElement fe;
                        fe.addArgument(transformedVector.at(i - 3));
                        fe.addArgument(transformedVector.at(i - 1));

                        ModulusFunctionElement *me = new ModulusFunctionElement(fe);
                        transformedVector.at(i - 1) = me;

                        transformedVector.erase(transformedVector.begin() + i); // removing operator (%)
                        tockens.erase(tockens.begin() + i);
                    }
                }
            }
        }

//		printTockens(tockens, transformedVector);

        //pass three //cos and sin
        for (unsigned int i = 0; i < tockens.size(); i++) { //cos
            if (tockenType(tockens.at(i)) == "cos") {
                if (i + 3 < tockens.size()) {
                    if (tockenType(tockens.at(i + 1)) == "lbracket" && tockenType(tockens.at(i + 3)) == "rbracket") {
                        if (i + 2 < transformedVector.size() && transformedVector.at(i + 2) != NULL) {
                            FunctionElement fe;
                            fe.addArgument(transformedVector.at(i + 2));
                            CosineFunctionElement *ce = new CosineFunctionElement(fe);
                            transformedVector.at(i) = ce;

                            transformedVector.erase(transformedVector.begin() + i + 1, transformedVector.begin() + i + 4);
                            tockens.erase(tockens.begin() + i + 1, tockens.begin() + i + 4);
                        }
                    }
                }
            }
        }
//		cout << endl << endl;
//		for (unsigned int i = 0; i < tockens.size(); i++) {
//			cout << tockens.at(i) << endl;
//		}
//		cout << endl;

        for (unsigned int i = 0; i < tockens.size(); i++) { //sin
            if (tockenType(tockens.at(i)) == "sin") {
                if (i + 3 < tockens.size()) {
                    if (tockenType(tockens.at(i + 1)) == "lbracket" && tockenType(tockens.at(i + 3)) == "rbracket") {
                        if (i + 2 < transformedVector.size() && transformedVector.at(i + 2) != NULL) {
                            FunctionElement fe;
                            fe.addArgument(transformedVector.at(i + 2));
                            SineFunctionElement *ce = new SineFunctionElement(fe);
                            transformedVector.at(i) = ce;

                            transformedVector.erase(transformedVector.begin() + i + 1, transformedVector.begin() + i + 4);
                            tockens.erase(tockens.begin() + i + 1, tockens.begin() + i + 4);
                        }
                    }

                }
            }
        }

        for (unsigned int i = 0; i < tockens.size(); i++) { //sin
            if (tockenType(tockens.at(i)) == "tan") {
                if (i + 3 < tockens.size()) {
                    if (tockenType(tockens.at(i + 1)) == "lbracket" && tockenType(tockens.at(i + 3)) == "rbracket") {
                        if (i + 2 < transformedVector.size() && transformedVector.at(i + 2) != NULL) {
                            FunctionElement fe;
                            fe.addArgument(transformedVector.at(i + 2));
                            TanFunctionElement *ce = new TanFunctionElement(fe);
                            transformedVector.at(i) = ce;

                            transformedVector.erase(transformedVector.begin() + i + 1, transformedVector.begin() + i + 4);
                            tockens.erase(tockens.begin() + i + 1, tockens.begin() + i + 4);
                        }
                    }

                }
            }
        }

        for (unsigned int i = 0; i < tockens.size(); i++) { //log
            if (tockenType(tockens.at(i)) == "log") {
                if (i + 3 < tockens.size()) {
                    if (tockenType(tockens.at(i + 1)) == "lbracket" && tockenType(tockens.at(i + 3)) == "rbracket") {
                        if (i + 2 < transformedVector.size() && transformedVector.at(i + 2) != NULL) {
                            FunctionElement fe;
                            fe.addArgument(transformedVector.at(i + 2));
                            LogFunctionElement *le = new LogFunctionElement(fe);
                            transformedVector.at(i) = le;

                            transformedVector.erase(transformedVector.begin() + i + 1, transformedVector.begin() + i + 4);
                            tockens.erase(tockens.begin() + i + 1, tockens.begin() + i + 4);
                        }
                    }

                }
            }
        }

//		printTockens(tockens, transformedVector);

        //pass five //divide and multiplication
        for (unsigned int i = 0; i < tockens.size(); i++) {
            if (tockenType(tockens.at(i)) == "divide") {
                if ((int) (i - 1) >= 0 && (i + 1 < transformedVector.size())) {
                    if (transformedVector.at(i - 1) != NULL && transformedVector.at(i + 1) != NULL) {
                        FunctionElement fe;
                        fe.addArgument(transformedVector.at(i - 1));
                        fe.addArgument(transformedVector.at(i + 1));
                        DivideFunctionElement *me = new DivideFunctionElement(fe);
                        transformedVector.at(i) = me;

                        transformedVector.erase(transformedVector.begin() + i - 1);
                        tockens.erase(tockens.begin() + i - 1);
                        transformedVector.erase(transformedVector.begin() + i); //when i-1 is erased , i+1 becomes i
                        tockens.erase(tockens.begin() + i);
                    }
                }
            }
        }
        //multiply elements like 2 and X
        for (unsigned int i = 0; i < tockens.size(); i++) {
            if (i >= 0 && i + 1 < transformedVector.size()) {
                if (transformedVector.at(i) != NULL && transformedVector.at(i + 1) != NULL) {
                    FunctionElement fe;
                    fe.addArgument(transformedVector.at(i));
                    fe.addArgument(transformedVector.at(i + 1));
                    MultipleFunctionElement *me = new MultipleFunctionElement(fe);
                    transformedVector.at(i) = me;

                    transformedVector.erase(transformedVector.begin() + i + 1);
                    tockens.erase(tockens.begin() + i + 1);
                }
            }
        }
        //multiply *
        for (unsigned int i = 0; i < tockens.size(); i++) {
            if (tockenType(tockens.at(i)) == "multiply") {
                if ((int) (i - 1) >= 0 && i + 1 < transformedVector.size()) {
                    if (transformedVector.at(i - 1) != NULL && transformedVector.at(i + 1) != NULL) {
                        FunctionElement fe;
                        fe.addArgument(transformedVector.at(i - 1));
                        fe.addArgument(transformedVector.at(i + 1));

                        MultipleFunctionElement *pe = new MultipleFunctionElement(fe);
                        transformedVector.at(i) = pe;

                        transformedVector.erase(transformedVector.begin() + i - 1);
                        tockens.erase(tockens.begin() + i - 1);
                        transformedVector.erase(transformedVector.begin() + i); //when i-1 is removed, i+1 becomes i
                        tockens.erase(tockens.begin() + i);
                    }
                }
            }
        }

        //multiply elements like X(anything)
        for (unsigned int i = 0; i < tockens.size(); i++) {
            if ((int) (i - 1) >= 0 && i + 2 < tockens.size()) {
                if (tockenType(tockens.at(i)) == "lbracket") {
                    if (transformedVector.at(i - 1) != NULL && transformedVector.at(i + 1) != NULL && tockenType(tockens.at(i + 2)) == "rbracket") {
                        FunctionElement fe;
                        fe.addArgument(transformedVector.at(i - 1));
                        fe.addArgument(transformedVector.at(i + 1));

                        MultipleFunctionElement *pe = new MultipleFunctionElement(fe);
                        transformedVector.at(i - 1) = pe;

                        transformedVector.erase(transformedVector.begin() + i);
                        tockens.erase(tockens.begin() + i); //removing bracket

                        transformedVector.erase(transformedVector.begin() + i); //removing right bracket
                        tockens.erase(tockens.begin() + i);

                        transformedVector.erase(transformedVector.begin() + i);
                        tockens.erase(tockens.begin() + i); //removing right bracket
                    }

                }

            }

        }

        //multiplying multiple brackets like ()()
        for (unsigned int i = 0; i < tockens.size(); i++) {
            if ((int) (i - 2) >= 0 && i + 3 < transformedVector.size()) {
                if (tockenType(tockens.at(i)) == "rbracket" && tockenType(tockens.at(i - 2)) == "lbracket" && transformedVector.at(i - 1) != NULL) {
                    if (tockenType(tockens.at(i + 1)) == "lbracket" && tockenType(tockens.at(i + 3)) == "rbracket" && transformedVector.at(i + 2) != NULL) {

                        FunctionElement fe;
                        fe.addArgument(transformedVector.at(i - 1));
                        fe.addArgument(transformedVector.at(i + 2));

                        MultipleFunctionElement *me = new MultipleFunctionElement(fe);
                        transformedVector.at(i - 2) = me;

                        transformedVector.erase(transformedVector.begin() + i);
                        tockens.erase(tockens.begin() + i); //removing element

                        transformedVector.erase(transformedVector.begin() + i);
                        tockens.erase(tockens.begin() + i); //removing bracket

                        transformedVector.erase(transformedVector.begin() + i);
                        tockens.erase(tockens.begin() + i); //removing bracket

                        transformedVector.erase(transformedVector.begin() + i);
                        tockens.erase(tockens.begin() + i); //removing element

                        transformedVector.erase(transformedVector.begin() + i - 1);
                        tockens.erase(tockens.begin() + i - 1); //removing bracket

                    }
                }
            }
        }

        //pass six // plus and minus

        for (unsigned int i = 0; i < tockens.size(); i++) { //plus
            if (tockenType(tockens.at(i)) == "plus" && (int) (i - 1) >= 0 && i + 2 < transformedVector.size()) {
                if (transformedVector.at(i - 1) != NULL && transformedVector.at(i + 1) != NULL && tockenType(tockens.at(i + 2)) != "lbracket") { //not adding x+2(
                    FunctionElement fe;
                    fe.addArgument(transformedVector.at(i - 1));
                    fe.addArgument(transformedVector.at(i + 1));

                    PlusFunctionElement *pe = new PlusFunctionElement(fe);
                    transformedVector.at(i) = pe;

                    transformedVector.erase(transformedVector.begin() + i - 1);
                    tockens.erase(tockens.begin() + i - 1);
                    transformedVector.erase(transformedVector.begin() + i); //when i-1 is removed, i+1 becomes i
                    tockens.erase(tockens.begin() + i);

                }

            }

            if (tockenType(tockens.at(i)) == "plus" && (int) (i - 1) >= 0 && i + 1 < transformedVector.size()) {
                if (transformedVector.at(i - 1) != NULL && transformedVector.at(i + 1) != NULL && tockens.size() <= 3) {

                    FunctionElement fe;
                    fe.addArgument(transformedVector.at(i - 1));
                    fe.addArgument(transformedVector.at(i + 1));

                    PlusFunctionElement *pe = new PlusFunctionElement(fe);
                    transformedVector.at(i) = pe;

                    transformedVector.erase(transformedVector.begin() + i - 1);
                    tockens.erase(tockens.begin() + i - 1);
                    transformedVector.erase(transformedVector.begin() + i); //when i-1 is removed, i+1 becomes i
                    tockens.erase(tockens.begin() + i);

                }

            }
        }
        for (unsigned int i = 0; i < tockens.size(); i++) { //plus
            if (tockenType(tockens.at(i)) == "plus" && i + 1 < tockens.size() && (int) (i - 3) >= 0 && tockenType(tockens.at(i - 1)) == "rbracket" && tockenType(tockens.at(i - 3)) == "lbracket" && transformedVector.at(i - 2) != NULL) {
                if (transformedVector.at(i + 1) != NULL) {
                    FunctionElement fe;
                    fe.addArgument(transformedVector.at(i - 2));
                    fe.addArgument(transformedVector.at(i + 1));

                    PlusFunctionElement *pe = new PlusFunctionElement(fe);
                    transformedVector.at(i - 3) = pe;

                    transformedVector.erase(transformedVector.begin() + i - 2);
                    tockens.erase(tockens.begin() + i - 2); //operator

                    transformedVector.erase(transformedVector.begin() + i - 2);
                    tockens.erase(tockens.begin() + i - 2); // )

                    transformedVector.erase(transformedVector.begin() + i - 2);
                    tockens.erase(tockens.begin() + i - 2); //operator

                    transformedVector.erase(transformedVector.begin() + i - 2);
                    tockens.erase(tockens.begin() + i - 2); //element
                }
            }
        }

        //minus
        for (unsigned int i = 0; i < tockens.size(); i++) { //minus

            if (tockenType(tockens.at(i)) == "minus" && (int) (i - 1) >= 0 && i + 2 < transformedVector.size()) {
                if (transformedVector.at(i - 1) != NULL && transformedVector.at(i + 1) != NULL && tockenType(tockens.at(i + 2)) != "lbracket") { //not adding x+2(
                    FunctionElement fe;
                    fe.addArgument(transformedVector.at(i - 1));
                    fe.addArgument(transformedVector.at(i + 1));

                    MinusFunctionElement *me = new MinusFunctionElement(fe);
                    transformedVector.at(i) = me;

                    transformedVector.erase(transformedVector.begin() + i - 1);
                    tockens.erase(tockens.begin() + i - 1);
                    transformedVector.erase(transformedVector.begin() + i); //when i-1 is removed, i+1 becomes i
                    tockens.erase(tockens.begin() + i);

                }

            }

            if (tockenType(tockens.at(i)) == "minus" && (int) (i - 1) >= 0 && i + 1 < transformedVector.size()) {
                if (transformedVector.at(i - 1) != NULL && transformedVector.at(i + 1) != NULL && tockens.size() <= 3) {
                    FunctionElement fe;
                    fe.addArgument(transformedVector.at(i - 1));
                    fe.addArgument(transformedVector.at(i + 1));

                    MinusFunctionElement *me = new MinusFunctionElement(fe);
                    transformedVector.at(i) = me;

                    transformedVector.erase(transformedVector.begin() + i - 1);
                    tockens.erase(tockens.begin() + i - 1);
                    transformedVector.erase(transformedVector.begin() + i); //when i-1 is removed, i+1 becomes i
                    tockens.erase(tockens.begin() + i);

                }

            }
        }
        for (unsigned int i = 0; i < tockens.size(); i++) { //plus
            if (tockenType(tockens.at(i)) == "minus" && i + 1 < tockens.size() && (int) (i - 3) >= 0 && tockenType(tockens.at(i - 1)) == "rbracket" && tockenType(tockens.at(i - 3)) == "lbracket" && transformedVector.at(i - 2) != NULL) {
                if (transformedVector.at(i + 1) != NULL) {
                    FunctionElement fe;
                    fe.addArgument(transformedVector.at(i - 2));
                    fe.addArgument(transformedVector.at(i + 1));

                    MinusFunctionElement *me = new MinusFunctionElement(fe);
                    transformedVector.at(i - 3) = me;

                    transformedVector.erase(transformedVector.begin() + i - 2);
                    tockens.erase(tockens.begin() + i - 2); //operator

                    transformedVector.erase(transformedVector.begin() + i - 2);
                    tockens.erase(tockens.begin() + i - 2); // )

                    transformedVector.erase(transformedVector.begin() + i - 2);
                    tockens.erase(tockens.begin() + i - 2); //operator

                    transformedVector.erase(transformedVector.begin() + i - 2);
                    tockens.erase(tockens.begin() + i - 2); //element

                }
            }
        }

    }

    FormulaElement *fe = new FormulaElement();
    if (transformedVector.at(0) != NULL) {
        return transformedVector.at(0);
    } else {
        return fe;
    }
}

void FormulaElement::printTockens(vector<string> tockens, vector<FormulaElement*> transformedVector) {
    cout << endl << "TOCKENS" << endl;
    for (unsigned int i = 0; i < tockens.size(); i++) {
        cout << i << ": " << tockens.at(i) << endl;
    }
    cout << endl;

    cout << endl << "TOCKENS at VECTOR" << endl;
    for (unsigned int i = 0; i < tockens.size(); i++) {
        if (transformedVector.at(i) != NULL) {
            cout << i << ": " << tockens.at(i) << endl;
        }
    }
    cout << endl;
    cout << "VECTOR" << endl;
    for (unsigned int i = 0; i < transformedVector.size(); i++) {
        if (transformedVector.at(i) != NULL) {
            cout << i << ": " << transformedVector.at(i)->toString() << endl;
        }
    }
    cout << endl;

    cout << "TOCKENS SIZE : " << tockens.size() << endl;
    cout << "VECTOR SIZE : " << transformedVector.size() << endl;

    cout << endl;
}

} //end of package


#endif // FORMULATOR_H

