
/**************************************
 *
 * University of Haifa
 *
 * Theory of compilation
 *
 * P machine compiler - code generation project
 *
 * Yosi Ben Asher
 * Email: yosibenasher@gmail.com
 *
 * Mariah Akree
 * Email: mariah.uni.haifa@gmail.com
 *
 **************************************/
/*   PROGRAM = 258,
 BBEGIN = 259,
 END = 260,
 DECLARE = 261,
 PROCEDURE = 262,
 FUNCTION = 263,
 LABEL = 264,
 INTEGER = 265,
 REAL = 266,
 RECORD = 267,
 BOOLEAN = 268,
 ARRAY = 269,
 OF = 270,
 ASSIGN = 271,
 LC = 272,
 RC = 273,
 IF = 274,
 THEN = 275,
 ELSE = 276,
 WHILE = 277,
 REPEAT = 278,
 FI = 279,
 DO = 280,
 OD = 281,
 READ = 282,
 WRITE = 283,
 TRUE = 284,
 FALSE = 285,
 ADD = 286,
 MIN = 287,
 MUL = 288,
 DIV = 289,
 GOTO = 290,
 MOD = 291,
 LES = 292,
 LEQ = 293,
 EQU = 294,
 NEQ = 295,
 GRE = 296,
 GEQ = 297,
 AND = 298,
 OR = 299,
 NOT = 300,
 CASE = 301,
 FOR = 302,
 FIN = 303,
 IDENTICAL = 304,
 FROM = 305,
 BY = 306,
 TO = 307,
 NEW = 308,
 INTCONST = 309,
 IDE = 310,
 REALCONST = 311,
 STRING = 312,
 DUMMY = 313*/

#ifndef AST_H
#define AST_H

#include <iostream>
#include <assert.h>
#include <string>
#include <iomanip>
#include <map>
#include <vector>

using namespace std;
static int end_if_counter = 0; // will help us know the number of if's
static int loop_counter = 0; // will help us know the number of loops
static int ind_flag = 1; // will help us know if we want to use ind
static int address_counter = 5; // address counter
static int increment_Decrement_op = 0; // will help us know the operand
static int ldc_or_inc_flag = 0; // if zero then we want to do add/sub. otherwise we want to do inc/dec
static int end_switch_counter = 0; // number of all switches
static int case_counter = 0; // will help us know the number of the currrent case
static int current_switch_counter = 0; // will help us know the number if the current switch
static int exp_dec_sub = 0;
static string temp_name;
static string rec_temp_name;
static int in_record_type = 0;
static int in_array_type = 0;
static int in_address_type = 0;
static int rec_start_address = 0;
static int d_counter = 1;
static vector<int > temp_low;
static vector<int > temp_d;
static int sizeOfType = 1;
static string sizeOfTname;
static int ixa_flag = 0;
static int begin_index = 1;
static int subpart_counter = 0;
static string arrayRefName;
static int creating_ide = 0;
static int inRecordRef_flag = 0;
static int inArrayRef_flag = 0;
static int addressRef_flag = 0;
static int new_flag = 0;
static vector<string> pointers_in_record;
static string newforString;
static int increment_flag = 0;
static int in_arrayRef_ind = 0;
static int in_recordRef_ind = 0;
static int in_addressRef_ind = 0;
static int expre_inArray = 0;
static string stringNew;
static string funcName;
static int program_flag = 0;
static string nameOfFather;
static int pro_func_flag = 0;
static int ssp = 5;
static int is_pro = 0;
static int is_func = 0;
static int last_func = 0;
static int lda_counter = 0;
static int byRef = 0;
static int callingFunc = 0;
static vector<string> parameters;
static int paraIndex = 0;
static string funCall;
static int funcDepth = 0;
static int cupCounter = 0;
static int func_is_parameter = 0;
static string func_Para_name;
static int retValue = 0;
static int sizeOfMovs = 0;
static int flagMovs = 0;
/**
 * classes
 */
class Node{
public:
    string name_; // name of variable
    int address_;
    double value_;
    int size_;
    int increment_;
    int sizeOfTYPE;
    Node* next_;
    vector< int > low_counter;
    vector< int > sizesOfArrays;
    string sizeOfTypeName;
    int byValOrbyRef_;

    // Default constructor
    Node()
    {
        name_ = "";
        increment_ = -1;
        address_ = 0;
        size_ = 0;
        value_ = 0;
        next_ = NULL;
        sizeOfTYPE = 1;
        byValOrbyRef_ = -1;
    }

    // Parameterised Constructor
    Node(double value, string type, int address, int size, int sizeOfTYPE, int increment, string sizeOfTypeName, int byValOrbyRef)
    {
        this->increment_ = increment;
        this->name_ = type;
        this->address_ = address;
        this->size_ = size;
        this->value_ = value;
        this->next_ = NULL;
        this->sizeOfTYPE = sizeOfTYPE;
        this->sizeOfTypeName =sizeOfTypeName;
        this->byValOrbyRef_ = byValOrbyRef;
    }
};

class Linkedlist{
    
    Node* head; // pointer to the head
public:
    Node* getHead()
    {
        return head;
    }

public:
    Linkedlist() { head = NULL; } // default constructor
    void insertNode(double data, string type, int address, int size, int sizeOFtype ,int inc, string sizeOfTypeName, int byValOrbyRef)
    {
        Node* newNode = new Node(data, type, address, size, sizeOFtype, inc, sizeOfTypeName, byValOrbyRef);

        
        if (head == NULL) // head is currently empty
        {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next_ != NULL) // here we are traversing on the list till  we reach the end.
        {
            // Update temp
            temp = temp->next_;
        }
        temp->next_ = newNode; //inserting node.
    }
    int findAddress(string nameOfVar)
    {
        int address = 0, flag = 1;
        Node* temp = head;
        while (temp && flag)
        {
            if(temp->name_ == nameOfVar) // searching for the name of varaible
            {
                flag = 0;
            }
            else
            {
                temp = temp->next_;
            }
        }
        address = temp->address_; // we found the address.
        return address;
    }
};
class func
{

public:
    map<string, Linkedlist*> map_;
    string name_;
    string father_;
    vector<string> parameters;
    int isParameter_;
    
    func(string name, string father,map<string, Linkedlist*> map_, vector<string> para, int isParameter)
    {
        this->name_ = name;
        this->father_ = father;
        this->map_ = map_;
        parameters = para;
        this->isParameter_ = isParameter;

    }
    map<string, Linkedlist*>& getMap(){return map_;}
    string getName() {return name_;}
    string getFather(){return father_;}
    vector<string> getVec(){return parameters;}
    void setManp(map<string, Linkedlist*> map){map_ = map;}
    void setFather(string str){ father_ = str;}
    void setVec(vector<string> vec){ parameters = vec;}

};
//static Linkedlist ST; // our Symbol Table
static map<string, Linkedlist*> mapOfHeads;
static map<string, Linkedlist*> mapOfProgram;
static map<string,func*> mapOfFuncs;
class Object {
public:
    virtual void print (ostream& os) = 0;
    virtual void pcodegen(ostream& os) = 0;
    virtual Object * clone () const {return NULL;}
    virtual ~Object () {}
};

class Expr : public Object {
    public :
    // Unary operations
    Expr (int op, Object * atom) : op_(op), atom_(atom), left_(NULL), right_(NULL), unary_(true) {}
    // Binary operations
    Expr (int op, Object * left, Object * right) : op_(op), left_(left), right_(right), atom_(NULL), unary_(false) {}

    Expr(const Expr & exp){
        unary_= exp.unary_;
        op_ = exp.op_;
        left_ = exp.left_->clone();
        right_ = exp.right_->clone();
        atom_ = exp.atom_->clone();
    }

    virtual ~Expr(){
        if (left_) delete left_;
        if (right_) delete right_;
        if (atom_) delete atom_;
    }


    void print (ostream& os) {
        os<<"Node name : Expr"<<endl;
        assert(op_);
        if (unary_)
        {
            os<<"Unary op is : "<<op_;
            assert(atom_);
            atom_->print(os);
        }
        else{
            os<<"Binary op is : "<<op_;
            assert(left_ && right_);
            right_->print(os);
            left_->print(os);
        }
    }
    void pcodegen(ostream& os) {
        assert(op_);
        exp_dec_sub = 1;
        if (unary_) {
            assert(atom_);
            atom_->pcodegen(os);

            if(op_== 287) // we want to use neg operation
            {
                os << "neg" << endl;
            }
            if(op_ == 300) // we want to use not operation
            {
                os << "not" << endl;
            }
        }
        else {
            assert(left_ && right_);
            int temp = ind_flag; // saving the value of ind_flag
            int temp2 = increment_Decrement_op;
            int temp3 = exp_dec_sub;
            int temp4 = in_recordRef_ind;
            int temp5 = in_arrayRef_ind;
            int temp6 = in_addressRef_ind;
            int temp7 =expre_inArray;
            ind_flag = 1; // here we will never need to use ind
            in_addressRef_ind = 1;
            in_arrayRef_ind = 1;
            in_recordRef_ind = 1;
            right_->pcodegen(os);
            in_addressRef_ind = 1;
            in_arrayRef_ind = 1;
            in_recordRef_ind = 1;
            ind_flag = 1; // here we will never need to use ind
            increment_Decrement_op = op_; // saving the operand to check if it's add or sub
            int temp1 = ldc_or_inc_flag; // saving the value of static variable cause it might change in the recursion calls
            exp_dec_sub = 0;
            expre_inArray = 1;
            left_->pcodegen(os);
            expre_inArray = temp7;
            exp_dec_sub = temp3;
            in_arrayRef_ind = temp5;
            in_recordRef_ind = temp4;
            in_addressRef_ind = temp6;
            ind_flag = temp; // reassinging the original value
            if(op_ == 296)
            {
                os << "grt" << endl;
            }
            if(op_== 286)
            {
                if(ldc_or_inc_flag == 0) // checking if the right son of the op_ is variable or constant, if variable we print add
                {
                    os << "add" << endl;
                }
            }
            if(op_== 287)
            {
                if(ldc_or_inc_flag == 0) // checking if the right son of the op_ is variable or constant, if variable we print sub
                {
                    os << "sub" << endl;
                }
            }
            if(op_== 288) // we want to use mul operation
            {
                os << "mul" << endl;
            }
            if(op_== 289) // we want to use div operation
            {
                os << "div" << endl;
            }
            if(op_== 292) // we want to usel les operation
            {
                os << "les" << endl;
            }
            if(op_== 293) // we want to use leq operation
            {
                os << "leq" << endl;
            }
            if(op_== 294) // we want to use equ operation
            {
                os << "equ" << endl;
            }
            if(op_== 295) // we want to use neq operation
            {
                os << "neq" << endl;
            }
            if(op_== 297) // we want to use geq operation
            {
                os << "geq" << endl;
            }
            if(op_== 298) // we want to use and operation
            {
                os << "and" << endl;
            }
            if(op_== 299) // we want to use or operation
            {
                os << "or" << endl;
            }
            ldc_or_inc_flag = temp1; // reassigning the origianl value
            increment_Decrement_op = temp2; // reassigning the origianl value
        }
    }
    virtual Object * clone () const { return new Expr(*this);}

private:
    bool unary_;
    int op_;
    Object * left_;
    Object * right_;
    Object * atom_;
};

class ExprList : public Object {
    public :
    ExprList (Object * expr) : expr_(expr),expr_list_(NULL){assert(expr_);}
    ExprList (Object * expr, Object * expr_list) : expr_(expr),expr_list_(expr_list) {assert(expr_ && expr_list_);}

    ExprList(const ExprList& exp){
        expr_ = exp.expr_->clone();
        expr_list_ = exp.expr_list_->clone();
    }

    virtual ~ExprList(){
        if (expr_) delete expr_;
        if (expr_list_) delete expr_list_;
    }

    void print (ostream& os) {
        os<<"Node name : ExprList";
        assert( expr_);
        expr_->print(os);
        if (expr_list_){
            expr_list_->print(os);
        }
    }
    void pcodegen(ostream& os) {
        assert(expr_);
//        ind_flag = 0; // here we will never need to use ind
//        int temp = ind_flag;
//        int temp4 = in_recordRef_ind;
//        int temp5 = in_arrayRef_ind;
//        int temp6 = in_addressRef_ind;
//        in_addressRef_ind = 0;
//        in_arrayRef_ind = 0;
//        in_recordRef_ind = 0;
        
        string tmp = mapOfFuncs.find(funCall)->second->getVec()[paraIndex++];
        //os << "name = " << tmp << endl;
        //os << "funcall = " << funCall << endl;
        int ind_temp = ind_flag;
        if(mapOfFuncs.find(funCall)->second->getMap().find(tmp)->second->getHead()->byValOrbyRef_)
        {
            ind_flag = 0;
            //os << "here1" << endl;
        }
        else
        {
            ind_flag = 1;
            //os << "here2" << endl;
        }
        expr_->pcodegen(os);
        if(flagMovs)
        {
            os << "movs " << sizeOfMovs << endl;
            flagMovs = 0;
        }
        ind_flag = ind_temp;
        if (expr_list_) {
            expr_list_->pcodegen(os);
        }
//        in_arrayRef_ind = temp5;
//        in_recordRef_ind = temp4;
//        in_addressRef_ind = temp6;
//        ind_flag = temp;
    }
    virtual Object * clone () const { return new ExprList(*this);}

private:
    Object * expr_;
    Object * expr_list_;
};

class Dim : public Object {
public:
    Dim (Object * exp) : exp_(exp), dim_(NULL) {assert(exp_);}
    Dim (Object * exp, Object * dim) : exp_(exp),dim_(dim) {assert(exp_ && dim_);}

    Dim(const Dim& d){
        exp_ = d.exp_->clone();
        dim_ = d.dim_->clone();
    }

    virtual ~Dim(){
        if (exp_) delete exp_;
        if (dim_) delete dim_;
    }

    void print (ostream& os) {
        os<<"Node name : Dim"<<endl;
        assert(exp_);
        exp_->print(os);
        if (dim_){
            dim_->print(os);
        }
    }
    void pcodegen(ostream& os) {
        assert(exp_);
        string tmp = arrayRefName;
        int temp4 = increment_flag;
        int temp5 = exp_dec_sub;
        exp_dec_sub = 1;
        increment_flag = 0;
        int temp2 = ind_flag;
        int temp3 = in_recordRef_ind;
        int temp6 = in_arrayRef_ind;
        int temp7 = in_addressRef_ind;
        ind_flag = 1;
        in_recordRef_ind = 1;
        in_arrayRef_ind = 1;
        in_addressRef_ind = 1;
        cout << "@@@@@@@@@@ start of Dim" << endl;
        exp_->pcodegen(os);
        cout << "@@@@@@@@@@ end of Dim" << endl;
        ind_flag = temp2;
        in_recordRef_ind = temp3;
        in_arrayRef_ind = temp6;
        in_addressRef_ind = temp7;
        exp_dec_sub = temp5;
        increment_flag = 0;
        arrayRefName = tmp;
        Linkedlist* temp;
        // arrayrefname is a pointer
        if(mapOfFuncs.find(funcName)->second->getMap().find(arrayRefName)->second->getHead()->size_ < mapOfFuncs.find(funcName)->second->getMap().find(arrayRefName)->second->getHead()->sizeOfTYPE)
        {
            string tmp = mapOfFuncs.find(funcName)->second->getMap().find(arrayRefName)->second->getHead()->sizeOfTypeName;
            temp = mapOfFuncs.find(funcName)->second->getMap().find(tmp)->second;
        }
        else // arrayref name is anything but pointer.
        {
            temp = mapOfFuncs.find(funcName)->second->getMap().find(arrayRefName)->second;
        }
        long d_len = temp->getHead()->sizesOfArrays.size();
        long low_len = temp->getHead()->low_counter.size();
        vector<int>::iterator itr1 = temp->getHead()->sizesOfArrays.begin();
        vector<int>::iterator itr2 = temp->getHead()->low_counter.begin();
        int sum_for_ixa = 1;
        if (begin_index < d_len)
        {
            for(long i = begin_index;  i < d_len; i++)
            {
                sum_for_ixa *= itr1[i];
            }
            begin_index++;
            os << "ixa " << sum_for_ixa* temp->getHead()->sizeOfTYPE << endl;
        }
        else if (begin_index == d_len)
        {
            os << "ixa " << sum_for_ixa * temp->getHead()->sizeOfTYPE<< endl;
            for(int i = 0 ; i < low_len; i++)
            {
                int dim_temp = 1;
                for(int j = i+1; j < d_len; j++)
                {
                    dim_temp *= itr1[j];
                }
                subpart_counter += dim_temp*itr2[i];
            }
            begin_index++;;
            subpart_counter *= temp->getHead()->sizeOfTYPE;
            
            os << "dec " << subpart_counter << endl;
            subpart_counter = 0;
        }
        if(begin_index > d_len)
        {
            arrayRefName = temp->getHead()->sizeOfTypeName;
            begin_index = 1;
        }
        if (dim_) {
            dim_->pcodegen(os);
        }
        ind_flag = temp2;
        increment_flag = temp4;
    }
    virtual Object * clone () const { return new Dim(*this);}

private:
    Object * exp_;
    Object * dim_;
};

class Atom : public Object {
};

class IntConst : public Atom {
public:
    IntConst(const int i) : i_(i) {}
    IntConst(const IntConst& in) : i_(in.i_) {}

    void print (ostream& os) {
        os<<"Node name : IntConst. Value is :"<<i_<<endl;
    }
    void pcodegen(ostream& os)
    {
        if(increment_Decrement_op == 286 && exp_dec_sub == 0) // if this expresion is true then we want to print inc
        {
            os << "inc " << i_ << endl;
            ldc_or_inc_flag = 1; //we want to print inc
            increment_Decrement_op = 0; // reseting the variable that holds the operand
        }
        else if(increment_Decrement_op == 287 && exp_dec_sub == 0) // if this expresion is true then we want to print dec
        {
            os << "dec " << i_ << endl;
            ldc_or_inc_flag = 1; //we want to print dec
            increment_Decrement_op = 0; // reseting the variable that holds the operand
        }
        else
        {
            if(callingFunc)
            {
                cupCounter++;
            }
            os << "ldc " << i_ << endl; // we want to print constant.
            increment_Decrement_op = 0;
        }
    }
    virtual Object * clone () const { return new IntConst(*this);}

private:
    const int i_;
};

class RealConst : public Atom {
public:
    RealConst(const double r) : r_(r) {}
    RealConst(const RealConst& in) : r_(in.r_) {}

    void print (ostream& os) {
        os<<"Node name : RealConst. Value is :"<<r_<<endl;
    }
    void pcodegen(ostream& os)
    {
        
        if(increment_Decrement_op == 286 && exp_dec_sub == 0) // if this expresion is true then we want to print inc
        {
             os << "inc " << r_ << endl;
            
            ldc_or_inc_flag = 1; //we want to print inc
            increment_Decrement_op = 0; // reseting the variable that holds the operand
        }
        else if(increment_Decrement_op == 287 && exp_dec_sub == 0) // if this expresion is true then we want to print dec
        {
             os << "dec " << r_ << endl;
            ldc_or_inc_flag = 1; //we want to print dec
            increment_Decrement_op = 0; // reseting the variable that holds the operand
        }
        else
        {
            if(callingFunc)
            {
                cupCounter++;
            }
            increment_Decrement_op = 0;
            os << std :: fixed << std :: setprecision(1) << "ldc " << r_ << endl; // we want to print constant.
        }
    }
    virtual Object * clone () const { return new RealConst(*this);}

private:
    const double r_;
};

class True : public Atom {
public:
    void print (ostream& os) {
        os<<"Node name : trueConst. Value is true"<<endl;
    }
    void pcodegen(ostream& os)
    {
        os << "ldc 1" << endl;
    }
    virtual Object * clone () const { return new True();}

};

class False : public Atom {
    public :
    void print (ostream& os) {
        os<<"Node name : trueConst. Value is false"<<endl;
    }
    void pcodegen(ostream& os)
    {
        os << "ldc 0" << endl;
    }
    virtual Object * clone () const { return new False();}
};

class Var : public Atom {
};

class ArrayRef : public Var {
    public :
    ArrayRef (Object * var, Object * dim) : var_(var),dim_(dim) {assert(var_ && dim_);}
    ArrayRef(const ArrayRef& arr){
        var_ = arr.var_->clone();
        dim_ = arr.dim_->clone();
    }

    virtual ~ArrayRef(){
        if (var_) delete var_;
        if (dim_) delete dim_;
    }

    void print (ostream& os) {
        os<<"Node name : ArrayRef"<<endl;
        assert(var_ && dim_);
        var_->print(os);
        dim_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(var_ && dim_);
        int temp1 = ind_flag;
        ind_flag = 0;
        int temp3 = inArrayRef_flag;
        int temp4 = in_arrayRef_ind;
        int temp5 = in_recordRef_ind;
        int temp6 = in_addressRef_ind;
        inArrayRef_flag = 1;
        in_arrayRef_ind = 0;
        in_recordRef_ind = 0;
        in_addressRef_ind = 0;
        var_->pcodegen(os);
        in_arrayRef_ind = temp4;
        in_recordRef_ind = temp5;
        in_addressRef_ind = temp6;
        ind_flag = temp1;
        ixa_flag = 1;
        ind_flag = temp1;
        dim_->pcodegen(os);
        if(in_arrayRef_ind)
        {
            os << "ind" << endl;
        }
        inArrayRef_flag = temp3;
        ixa_flag = 0;
    }
    virtual Object * clone () const { return new ArrayRef(*this);}

private:
    Object * var_;
    Object * dim_;
};

class RecordRef : public Var {
    public :
    RecordRef (Object * varExt, Object * varIn) : varExt_(varExt),varIn_(varIn) {assert(varExt_ && varIn_);}
    RecordRef(const RecordRef& rec){
        varExt_ = rec.varExt_->clone();
        varIn_ = rec.varIn_->clone();
    }

    virtual ~RecordRef(){
        if (varExt_) delete varExt_;
        if (varIn_) delete varIn_;
    }

    void print (ostream& os) {
        os<<"Node name : RecordRef"<<endl;
        assert(varExt_ && varIn_);
        varExt_->print(os);
        varIn_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(varExt_ && varIn_);
        int temp_ind_flag = ind_flag;
        ind_flag = 0;
        int temp3 = inRecordRef_flag;
        int temp2 = new_flag;
        int temp4 = expre_inArray;
        int temp5 = in_addressRef_ind;
        int temp6 = in_arrayRef_ind;
        int temp7 = in_recordRef_ind;
        new_flag = 0;
        inRecordRef_flag = 1;
        expre_inArray = 1;
        in_addressRef_ind = 0;
        in_recordRef_ind = 0;
        in_arrayRef_ind = 0;
        varExt_->pcodegen(os);
        expre_inArray = 0;
        ind_flag = temp_ind_flag;
        new_flag = temp2;
        increment_flag = 1;
    
        in_recordRef_ind = temp7;
        in_addressRef_ind = temp5;
        in_arrayRef_ind = temp6;
        ind_flag = temp_ind_flag;
        varIn_->pcodegen(os);
        expre_inArray = temp4;

        increment_flag = 0;
        //ind_flag = temp_ind_flag;
        inRecordRef_flag = temp3;
    }
    virtual Object * clone () const { return new RecordRef(*this);}

private:
    Object * varExt_;
    Object * varIn_;
};

class AddressRef : public Var {
    public :
    AddressRef (Object * var) : var_(var) {assert(var_);}
    AddressRef(const AddressRef& addre){
        var_ = addre.var_->clone();
    }

    virtual ~AddressRef(){
        if (var_) delete var_;
    }

    void print (ostream& os) {
        os<<"Node name : AddressRef"<<endl;
        assert(var_);
        var_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(var_);
        int temp = addressRef_flag;
        int temp2 = ind_flag;
        addressRef_flag = 1;
        ind_flag = 0;
        int temp3 = in_recordRef_ind;
        int temp4 = in_arrayRef_ind;
        int temp5 = in_addressRef_ind;
        in_recordRef_ind = 0;
        in_arrayRef_ind = 0;
        in_addressRef_ind = 0;
        var_->pcodegen(os);
        in_addressRef_ind = temp5;
        in_recordRef_ind = temp3;
        in_arrayRef_ind = temp4;
        ind_flag = temp2;
        os << "ind" << endl;
        if(in_addressRef_ind)
        {
            os << "ind" << endl;
        }
        if(new_flag && stringNew != "Fixed")
        {
            stringNew = mapOfFuncs.find(funcName)->second->getMap().find(stringNew)->second->getHead()->sizeOfTypeName;
        }
        addressRef_flag = temp;
    }
    virtual Object * clone () { return new AddressRef(*this);}

private:
    Object * var_;
};

class Statement : public Object {
};

class NewStatement : public Statement {
    public :
    NewStatement (Object * var) : var_(var) {assert(var_);}
    NewStatement(const NewStatement& ns){
        var_ = ns.var_->clone();
    }

    virtual ~NewStatement(){
        if (var_) delete var_;
    }

    void print (ostream& os) {
        os<<"Node name : NewStatement";
        assert(var_);
        var_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(var_);
        int temp = new_flag;
        new_flag = 1;
        int temp2 = ind_flag;
        ind_flag = 0;
        int temp_ind = ind_flag;
        int temp_arr = in_arrayRef_ind;
        int temp_add = in_addressRef_ind;
        int temp_rec = in_recordRef_ind;
        ind_flag = 0;
        in_recordRef_ind = 0;
        in_addressRef_ind = 0;
        in_arrayRef_ind = 0;
        var_->pcodegen(os);
        in_recordRef_ind = temp_rec;
        in_addressRef_ind = temp_add;
        in_arrayRef_ind = temp_arr;
        ind_flag = temp_ind;
        ind_flag = temp2;
        if (new_flag)
        {
            //cout << "newString = " << stringNew << endl;
            os << "ldc " << mapOfFuncs.find(funcName)->second->getMap().find(stringNew)->second->getHead()->sizeOfTYPE << endl;
        }
        os << "new" << endl;
        new_flag = temp;
    }
    virtual Object * clone () { return new NewStatement(*this);}

private:
    Object * var_;
};

class WriteStrStatement : public Statement {
    public :
    WriteStrStatement (const char * str) {
        str_ = new string(str);
    }

    WriteStrStatement(const WriteStrStatement& ns){
        str_ = new string(*ns.str_);
    }

    virtual ~WriteStrStatement () {
        if (str_) delete str_;
    }
    void print (ostream& os) {
        os<<"Node name : WriteStrStatement";
        assert(str_);
        os<<"Str statement is: "<<str_<<endl;
    }
    void pcodegen(ostream& os) {
        assert(str_);
    }
    virtual Object * clone () { return new WriteStrStatement(*this);}

private:
    string * str_;
};

class WriteVarStatement : public Statement {
    public :
    WriteVarStatement (Object * exp) : exp_(exp) {assert(exp_);}

    WriteVarStatement(const WriteVarStatement& ex){
        exp_ = ex.clone();
    }

    virtual ~WriteVarStatement(){
        if (exp_) delete exp_;
    }

    void print (ostream& os) {
        os<<"Node name : WriteVarStatement";
        assert(exp_);
        exp_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(exp_);
        int temp1 = in_arrayRef_ind;
        int temp2 = in_recordRef_ind;
        int temp3 = in_addressRef_ind;
        int temp4 = ind_flag;
        ind_flag = 1;
        in_addressRef_ind = 1;
        in_arrayRef_ind = 1;
        in_recordRef_ind = 1;
        exp_->pcodegen(os);
        ind_flag = temp4;
        in_addressRef_ind = temp3;
        in_arrayRef_ind = temp1;
        in_recordRef_ind = temp2;
        os << "print" << endl;
    }
    virtual Object * clone () const { return new WriteVarStatement(*this);}

private:
    Object * exp_;
};

class ProcedureStatement : public Statement {
    public :
    ProcedureStatement (const char * str) {
        str_ = new string(str);
    }

    ProcedureStatement (Object * expr_list, const char * str) : expr_list_(expr_list) {
        assert(expr_list_);
        str_ = new string(str);
    }

    ProcedureStatement(const ProcedureStatement& ps){
        expr_list_ = ps.expr_list_->clone();
        str_ = new string(*ps.str_);
    }

    virtual ~ProcedureStatement () {
        if (str_) delete str_;
        if (expr_list_) delete expr_list_;
    }

    void print (ostream& os) {
        os<<"Node name : ProcedureStatement. Proc name : "<< *str_<<endl;
        if (expr_list_ ){
            expr_list_->print(os);
        }
    }
    void pcodegen(ostream& os)
    {
        cout << "start of PROstatment " << endl;
        callingFunc = 1;
        funCall = *str_;
        //vector<string> vec = mapOfFuncs.find(funCall)->second->getVec();
        int temp1 = ind_flag;
        ind_flag = 0;
        paraIndex = 0;
        string tmp = mapOfFuncs.find(funCall)->second->getFather() == "NULL" ? mapOfFuncs.find(funCall)->second->getName(): mapOfFuncs.find(funCall)->second->getFather();
        cout << "jj" << endl;
        string temp2 = funcName;
        cout << "tmp = " << tmp << endl;
        while (funcName != tmp)
        {
            funcName = mapOfFuncs.find(funcName)->second->getFather();
            funcDepth++;
        }
        cout << "jj" << endl;
        funcName = temp2;
        //string temp3 = mapOfFuncs.find(*str_)->second->getFather();
        //os << "temp3 = "<< temp3 << endl;
        int i = 0, flag = 1;
        string str4 , str3 = funcName;
        while(funcName != "NULL")
        {
            while( i < mapOfFuncs.find(funcName)->second->getVec().size())
            {
                if(mapOfFuncs.find(funcName)->second->getVec()[i] == *str_)
                {
                    flag = 0;
                    str4 = funcName;
                }
                cout << mapOfFuncs.find(funcName)->second->getVec()[i] << endl;
                i++;
            }
            cout << "before funcName = " << funcName << endl;
            funcName = mapOfFuncs.find(funcName)->second->getFather();
            cout << "after funcName = " << funcName << endl;
            i = 0;
        }
        funcName = str3;
        if(!flag)
        {
            //cout << "hhh bith" << endl;
            os << "mstf " << --funcDepth << " " << mapOfFuncs.find(str4)->second->getMap().find(*str_)->second->getHead()->address_ << endl;
            funcDepth++;
        }
        else
        {
            os << "mst " << funcDepth << endl;
        }
        cout << "mst " << funcDepth << endl;
        //int temp_exp_dec_sub = exp_dec_sub;
        //exp_dec_sub = 1;
        if (expr_list_) {
            expr_list_->pcodegen(os);
        }
        //exp_dec_sub = temp_exp_dec_sub;
        cupCounter = 0;
        func* tm = mapOfFuncs.find(*str_)->second;
        for(int i = 0; i <tm->getVec().size(); i++ )
        {
            cupCounter += tm->getMap().find(tm->getVec()[i])->second->getHead()->size_;
        }
        if(!flag)
        {
            os << "smp " << cupCounter << endl;
            os << "cupi " << --funcDepth << " " << mapOfFuncs.find(str4)->second->getMap().find(*str_)->second->getHead()->address_ << endl;
        }
        else
        {
            func* tm = mapOfFuncs.find(*str_)->second;
            os << "cup " << cupCounter << " " << *str_ << endl;
        }
        cupCounter = 0;
        funcDepth = 0;
        cout << "end of PROstatment " << endl;
        ind_flag = temp1;
        callingFunc = 0;
        //mapOfFuncs.find(funCall)->second->getVec() = vec;
        
    }
    virtual Object * clone () const { return new ProcedureStatement(*this);}

private:
    Object * expr_list_;
    string * str_;
};

class Case : public Object {
    public :
    Case (Object * stat_list, int val) : leafChild_ (NULL), stat_list_(stat_list) {
        // note the special treatment in miny.y for this case (makenode)
        leafChild_ = new IntConst(val);
        assert(stat_list_);
    }

    Case(const Case& c){
        stat_list_ = c.stat_list_->clone();
        leafChild_ = c.leafChild_->clone();
    }

    virtual ~Case () {
        if (stat_list_) delete stat_list_;
        if (leafChild_) delete leafChild_;
    }

    void print (ostream& os) {
        os<<"Node name : Case";
        assert(stat_list_);
        stat_list_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(stat_list_);
        // case counter will help us know the case number
        os << "case_" << ++case_counter << "_" << current_switch_counter << ":" << endl; // printing the currrent case
        int temp = current_switch_counter;
        stat_list_->pcodegen(os);
        current_switch_counter = temp;
        os << "ujp end_switch_" <<  current_switch_counter << endl; // jumping to the end of switch i
    }
    virtual Object * clone () const { return new Case(*this);}

private:
    Object * stat_list_;
    Object * leafChild_;
};


class CaseList : public Object {
    public :
    CaseList (Object * ccase) : case_(ccase),case_list_(NULL) {assert(case_);}
    CaseList (Object * ccase, Object * case_list) : case_(ccase),case_list_(case_list) {assert(case_ && case_list_);}

    CaseList(const CaseList& cl){
        case_ = cl.case_->clone();
        case_list_ = cl.case_list_->clone();
    }

    virtual ~CaseList () {
        if (case_) delete case_;
        if (case_list_) delete case_list_;
    }

    void print (ostream& os) {
        os<<"Node name : CaseList";
        assert( case_ );
        case_->print(os);
        if (case_list_){
            case_list_->print(os);
        }
    }
    void pcodegen(ostream& os) {
        assert(case_);
        case_->pcodegen(os);
        if (case_list_) {
            case_list_->pcodegen(os);
        }
    }
    virtual Object * clone () const { return new CaseList(*this);}

private:
    Object * case_;
    Object * case_list_;
};

class CaseStatement : public Statement {
    public :
    CaseStatement (Object * exp, Object * case_list) : exp_(exp),case_list_(case_list) {assert(exp_ && case_list_);}

    CaseStatement(const CaseStatement& cs){
        exp_ = cs.exp_->clone();
        case_list_ = cs.case_list_->clone();
    }

    virtual ~CaseStatement () {
        if (exp_) delete exp_;
        if (case_list_) delete case_list_;
    }

    void print (ostream& os) {
        os<<"Node name : CaseStatement";
        assert( exp_ && case_list_);
        exp_->print(os);
        case_list_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(exp_ && case_list_);
        int temp_ind = ind_flag;
        int temp_arr = in_arrayRef_ind;
        int temp_add = in_addressRef_ind;
        int temp_rec = in_recordRef_ind;
        ind_flag = 1;
        in_recordRef_ind = 1;
        in_addressRef_ind = 1;
        in_arrayRef_ind = 1;
        exp_->pcodegen(os);
        in_recordRef_ind = temp_rec;
        in_addressRef_ind = temp_add;
        in_arrayRef_ind = temp_arr;
        ind_flag = temp_ind;
        os << "neg" << endl << "ixj end_switch_" << ++end_switch_counter << endl; // after the expression of the switch we print
        int temp1 = case_counter; // saving the current number of cases of switch_i
        case_counter = 0; // reseting the variable to zero to start a new switch, and count new cases
        current_switch_counter = end_switch_counter; // current number of switches
        int temp = end_switch_counter; // saving the number of switches
        case_list_->pcodegen(os);
        for(int i = case_counter ; i > 0; i--) // printing all the cases j at each switch i
        {
            os << "ujp case_" << i << "_" << temp << endl;
        }
        os << "end_switch_" << temp << ":"<< endl; // end of switch i

        case_counter = temp1; // reassigning the number of cases
        if(case_counter > 0) // checks if in a case j there is an inner switch i, we need to know where to countinue after finishing switch i, and that will be at case j+1, at switch i-1
        {
            current_switch_counter = temp-1; // assigning the number of previous switch
        }
        else
        {
            current_switch_counter = temp; // assigning the number of current switch
        }

    }
    virtual Object * clone () const { return new CaseStatement(*this);}

private:
    Object * exp_;
    Object * case_list_;
};

class LoopStatement : public Statement {
    public :
    LoopStatement (Object * exp, Object * stat_list) : exp_(exp),stat_list_(stat_list) {assert(exp_ && stat_list_);}

    LoopStatement(const LoopStatement& ls){
        exp_ = ls.exp_->clone();
        stat_list_ = ls.stat_list_->clone();
    }

    virtual ~LoopStatement () {
        if (exp_) delete exp_;
        if (stat_list_) delete stat_list_;
    }

    void print (ostream& os) {
        os<<"Node name : LoopStatement";
        assert( exp_ && stat_list_);
        exp_->print(os);
        stat_list_->print(os);
    }
    void pcodegen(ostream& os) {
        int temp_end_loop;
        assert(exp_ && stat_list_);
        os << "loop_" << ++loop_counter  << ":" << endl;
        temp_end_loop = loop_counter; // saving the current number of loops
        int temp_ind = ind_flag;
        int temp_arr = in_arrayRef_ind;
        int temp_add = in_addressRef_ind;
        int temp_rec = in_recordRef_ind;
        ind_flag = 1;
        in_recordRef_ind = 1;
        in_addressRef_ind = 1;
        in_arrayRef_ind = 1;
        exp_->pcodegen(os);
        in_recordRef_ind = temp_rec;
        in_addressRef_ind = temp_add;
        in_arrayRef_ind = temp_arr;
        ind_flag = temp_ind;
        os << "fjp end_loop_" << temp_end_loop << endl; // after the expresstion we do a fjp
        stat_list_->pcodegen(os);
        os << "ujp loop_" << temp_end_loop << endl; // a way to jump to loop if the expression is true
        os << "end_loop_" << temp_end_loop << ":" << endl; // end of loop
    }
    virtual Object * clone () const { return new LoopStatement(*this);}

private:
    Object * exp_;
    Object * stat_list_;
};


class ConditionalStatement : public Statement {
    public :
    ConditionalStatement (Object * exp, Object * stat_list_if) : exp_(exp),stat_list_if_(stat_list_if), stat_list_else_(NULL) {assert(exp_ && stat_list_if_);}
    ConditionalStatement (Object * exp, Object * stat_list_if, Object * stat_list_else) : exp_(exp),stat_list_if_(stat_list_if), stat_list_else_(stat_list_else) {assert(exp_ && stat_list_if_ && stat_list_else_ );}

    ConditionalStatement(const ConditionalStatement& cs){
        exp_ = cs.exp_->clone();
        stat_list_if_ = cs.stat_list_if_->clone();
        stat_list_else_ = cs.stat_list_else_->clone();
    }

    virtual ~ConditionalStatement () {
        if (exp_) delete exp_;
        if (stat_list_if_) delete stat_list_if_;
        if (stat_list_else_) delete stat_list_else_;
    }

    void print (ostream& os) {
        os<<"Node name : ConditionalStatement";
        assert( exp_ && stat_list_if_);

        exp_->print(os);

        stat_list_if_->print(os);
        if (stat_list_else_){
            stat_list_else_->print(os);
        }
    }
    void pcodegen(ostream& os) {
        int temp_end_if, temp_else_if;
        assert(exp_ && stat_list_if_);
        int temp_ind = ind_flag;
        int temp_arr = in_arrayRef_ind;
        int temp_add = in_addressRef_ind;
        int temp_rec = in_recordRef_ind;
        ind_flag = 1;
        in_recordRef_ind = 1;
        in_addressRef_ind = 1;
        in_arrayRef_ind = 1;
        exp_->pcodegen(os);
        in_recordRef_ind = temp_rec;
        in_addressRef_ind = temp_add;
        in_arrayRef_ind = temp_arr;
        ind_flag = temp_ind;
        if(stat_list_else_)
        {
            
            temp_end_if = end_if_counter;
            end_if_counter++;
            os << "fjp else_if_" << ++temp_end_if << endl; // after the expresstion we do a fjp
            stat_list_if_->pcodegen(os);
            os << "ujp end_if_" << temp_end_if << endl; // end of if
            os << "else_if_" <<temp_end_if << ":" << endl; //start of the label else if
            stat_list_else_->pcodegen(os);
            os << "end_if_" << temp_end_if << ":" << endl; // end of if
        }
        else
        {
            os << "fjp end_if_" << ++end_if_counter << endl; // after the expresstion we do a fjp
            temp_end_if = end_if_counter; // saving the current number of if's
            stat_list_if_->pcodegen(os);
            os << "end_if_" << temp_end_if << ":" << endl; // end of if
        }
    }
    virtual Object * clone () const { return new ConditionalStatement(*this);}

private:
    Object * exp_;
    Object * stat_list_if_;
    Object * stat_list_else_;
};


class Assign : public Statement {
    public :
    Assign (Object * var, Object * exp) : var_(var), exp_(exp) {assert(var_ && exp_);}

    Assign(const Assign& as){
        var_ = as.var_->clone();
        exp_ = as.exp_->clone();
    }

    virtual ~Assign () {
        if (exp_) delete exp_;
        if (var_) delete var_;
    }

    void print (ostream& os) {
        os<<"Node name : Assign";
        assert(var_ && exp_);
        exp_->print(os);
        var_->print(os);
    }
    void pcodegen(ostream& os) {
        int temp = ind_flag; //saving the value of variable
        assert(var_ && exp_);
        ind_flag = 0; //before looking at the variable we dont want to print ind so the flag has the value zero
        //in_arrayRef_ind = 1;
        int temp2 = in_arrayRef_ind;
        int temp3 = in_recordRef_ind;
        int temp4 = in_addressRef_ind;
        int temp5 = retValue;
        in_arrayRef_ind = 0;
        in_recordRef_ind = 0;
        in_addressRef_ind = 0;
        retValue = 1;
        exp_->pcodegen(os);
        retValue = 0;
        ind_flag = 1; //after looking at the variable we might need to print ind so the flag has the value zero
        in_arrayRef_ind = 1;
        in_recordRef_ind = 1;
        in_addressRef_ind = 1;
        var_->pcodegen(os);
        retValue = temp5;
        in_addressRef_ind = temp4;
        in_arrayRef_ind = temp2;
        in_recordRef_ind = temp3;
        os << "sto" << endl;
        ind_flag = temp; // reassigning the old value
//        for(auto it = mapOfHeads.cbegin(); it != mapOfHeads.cend(); ++it){
//
//            std::cout << it->first << " name: " <<it->second->getHead()->name_ <<" address: "<< it->second->getHead()->address_ << " size: " << it->second->getHead()->size_ << " sizeOfTYPE: " << it->second->getHead()->sizeOfTYPE << "sizeof " << it->second->getHead()->sizeOfTypeName << " sizeofvector = " <<it->second->getHead()->sizesOfArrays.size() << " typename = " << it->second->getHead()->sizeOfTypeName << "  increment = " << it->second->getHead()->increment_;
//
//        cout<<endl;
//        }
//        cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;

    }
    virtual Object * clone () const { return new Assign(*this);}

private:
    Object * var_;
    Object * exp_;
};

class StatementList : public Object {
    public :
    StatementList (Object * stat) : stat_list_(NULL), stat_(stat)  { assert(stat_);}
    StatementList (Object * stat_list, Object * stat) : stat_list_(stat_list),stat_(stat)  {assert(stat_list_ && stat);}

    StatementList (const StatementList& sl){
        stat_ = sl.stat_->clone();
        stat_list_ = sl.stat_list_->clone();
    }

    virtual ~StatementList () {
        if (stat_) delete stat_;
        if (stat_list_) delete stat_list_;
    }

    void print (ostream& os) {
        os<<"Node name : StatementList"<<endl;
        if (stat_list_){
            stat_list_->print(os);
        }
        assert(stat_);
        stat_->print(os);
    }
    void pcodegen(ostream& os) {
        if (stat_list_) {
            stat_list_->pcodegen(os);
        }
        assert(stat_);
        stat_->pcodegen(os);
    }
    virtual Object * clone () const { return new StatementList(*this);}

private:
    Object * stat_;
    Object * stat_list_;
};

class RecordList : public Object {
    public :
    RecordList (Object * var_decl) : record_list_(NULL), var_decl_(var_decl)  { assert(var_decl_);}
    RecordList (Object * record_list, Object * var_decl) : record_list_(record_list),var_decl_(var_decl)  {assert(record_list_ && var_decl);}

    RecordList(const RecordList& li){
        var_decl_= li.var_decl_->clone();
        record_list_ = li.record_list_->clone();
    }

    virtual ~RecordList () {
        if (var_decl_) delete var_decl_;
        if (record_list_) delete record_list_;
    }

    void print (ostream& os) {
        os<<"Node name : RecordList"<<endl;
        if (record_list_){
            record_list_->print(os);
        }
        assert(var_decl_);
        var_decl_->print(os);
    }
    void pcodegen(ostream& os) {
        if (record_list_) {
            record_list_->pcodegen(os);
        }
        assert(var_decl_);
        var_decl_->pcodegen(os);
    }
    virtual Object * clone () const { return new RecordList(*this);}

private:
    Object * var_decl_;
    Object * record_list_;
};

class Type : public Object {
};

class SimpleType : public Type {
public:
    SimpleType (const char * name) {
        name_ = new string(name);
    }

    virtual ~SimpleType () {
        if (name_ )delete name_;
    }

    SimpleType(const SimpleType& s){
        name_ = new string(*s.name_);
    }

    void print (ostream& os) {
        os<<"Node name : SimpleType"<<endl;;
        os<<"Type is : "<< (*name_) <<endl;
    }
    void pcodegen(ostream& os)
    {
        sizeOfTname = "Fixed";
    }
    virtual Object * clone () const { return new SimpleType(*this);}

private:
    string * name_;
};

class IdeType : public Type {
public:
    IdeType (const char * name) {
        name_ = new string(name);
    }

    virtual ~IdeType () {
        if (name_) delete name_;
    }

    IdeType(const IdeType& s){
        name_ = new string(*s.name_);
    }

    void print (ostream& os) {
        os<<"Node name : IdeType"<<endl;
    }
    void pcodegen(ostream& os)
    {
        cout << "IDETYPE" << endl;
        cout << "name in idetype " << *name_ << endl;
        cout <<"funcName" << funcName << endl;
        map<string, Linkedlist*> map = mapOfFuncs.find(funcName)->second->getMap();
        cout << "fff" <<endl;
        //cout << mapOfFuncs.find(funcName)->second->getMap().find(*name_)->second->getHead()->name_ << "is in map" << endl;
        cout << "siu" << endl;
        string tempFuncName = funcName;
        int flag = 1;
        if(mapOfFuncs.find(*name_) != mapOfFuncs.end())
        {
            if(retValue)
            {
                flag = 0;
            }
        }
        else
        {
            if(retValue)
            {
                flag = 1;
            }
            else
            {
                flag = 1;
            }
        }
        if(creating_ide && mapOfFuncs.find(*name_) != mapOfFuncs.end()) // we are defining a function by another function
        {
            func_is_parameter = 1;
            func_Para_name = *name_;
            //cout << "lollele" << endl;
        }
       else if(!func_is_parameter && flag) // return value of function
       {
           if(mapOfFuncs.find(*name_) == mapOfFuncs.end())
           {
               while(map.find(*name_) == map.end() && !creating_ide) //element is not in the current func
               {
                   cout << "current name = " << funcName << endl;
                   funcName = mapOfFuncs.find(funcName)->second->getFather();
                   map = mapOfFuncs.find(funcName)->second->getMap();
                   //            for(auto it = map.cbegin(); it != map.cend(); ++it){
                   //
                   //                std::cout << it->first << " name: " <<it->second->getHead()->name_ <<" address: "<< it->second->getHead()->address_ << " size: " << it->second->getHead()->size_ << " sizeOfTYPE: " << it->second->getHead()->sizeOfTYPE << "sizeof " << it->second->getHead()->sizeOfTypeName << " sizeofvector = " <<it->second->getHead()->sizesOfArrays.size() << " typename = " << it->second->getHead()->sizeOfTypeName << "  increment = " << it->second->getHead()->increment_;
                   //
                   //                cout<<endl;
                   //            }
                   //            cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
                   cout << "in here" << endl;
                   cout << "after name = " << funcName << endl;
                   lda_counter++;
               }
               funcName = tempFuncName;
               cout << "u6" << endl;
               
               if(in_address_type && in_record_type)
               {
                   cout << "u1" << endl;
                   if(rec_temp_name != *name_)
                   {
                       sizeOfType = map.find(*name_)->second->getHead()->size_;
                       sizeOfTname = *name_;
                       arrayRefName = *name_;
                   }
                   else
                   {
                       pointers_in_record.push_back(temp_name);
                   }
               }
               else
               {
                   cout << "u2" << endl;
                   if(in_array_type || in_address_type)
                   {
                       sizeOfType = map.find(*name_)->second->getHead()->size_;
                   }
                   else
                   {
                       sizeOfType = map.find(*name_)->second->getHead()->sizeOfTYPE;
                   }
                   sizeOfTname = *name_;
                   arrayRefName = *name_;
               }
               //        cout << "********* PCODE GEN OF IDETYPE ******** name is: " << *name_ << endl;
               //        cout << "%%%%%%%%%% inRecordRef_flag = " << inRecordRef_flag << endl;
               //        cout << "%%%%%%%%%% new_flag = " << new_flag << endl;
               //        cout << "%%%%%%%%%% addressRef_flag = " << addressRef_flag << endl;
               if(!creating_ide)
               {
                   if(addressRef_flag && !increment_flag)
                   {
                       cout << "u3" << endl;
                       os << "lda ";
                       if(!callingFunc)
                       {
                           os << lda_counter;
                       }
                       else
                       {
                           os << funcDepth;
                       }
                       os << " " << map.find(*name_)->second->getHead()->address_ << endl;
                   }
                   else if (increment_flag)
                   {
                       cout << "u4" << endl;
                       os << "inc " << map.find(*name_)->second->getHead()->increment_ << endl;
                       if (ind_flag || in_recordRef_ind)
                       {
                           os << "ind" << endl;
                       }
                   }
                   else
                   {
                       cout << "u5" << endl;
                       os << "lda " << lda_counter;
                       //                    if(!callingFunc)
                       //                    {
                       //                        os << lda_counter;
                       //                        cout << "lda_counter = " <<  lda_counter << endl;
                       //                    }
                       //                    else
                       //                    {
                       //                        os << funcDepth;
                       //                        cout << "funcDepth = " << funcDepth << endl;
                       //                    }
                       os << " " << map.find(*name_)->second->getHead()->address_ << endl;
                       // && !callingFunc
                       //os << "ind_flag = " << ind_flag << endl;
                       if ((ind_flag || in_recordRef_ind))
                       {
                           
                           os << "ind" << endl;
                       }
                   }
                   if (new_flag)
                   {
                       //cout << "name = " << *name_ << endl;
                       stringNew = *name_;
                       //os << "ldc " << mapOfHeads.find(*name_)->second->getHead()->sizeOfTYPE << endl;
                   }
               }
           }
               //cout << "name " << map.find(*name_)->second->getHead()->name_ << ", byRef = " << map.find(*name_)->second->getHead()->byValOrbyRef_ << endl;
           cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^&&&&&&&&&&&&&&&&&&&&&&^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
           if(callingFunc)
           {
               cout << "b cupCounter = " << cupCounter << endl;
               cout << "a cupCounter = " << cupCounter << endl;
               //string tmp = mapOfFuncs.find(funCall)->second->getVec()[paraIndex];
               //cout << "vec[paraIndex] = " << mapOfFuncs.find(funCall)->second->getVec()[paraIndex] << endl;
               //cout << "tmp = " << tmp << endl;
               cout << "callingFunc = " << callingFunc << endl;
               if(mapOfFuncs.find(*name_) != mapOfFuncs.end())
               {
                   int d= 0;
                   string tmp = mapOfFuncs.find(*name_)->second->getFather() == "NULL" ? mapOfFuncs.find(*name_)->second->getName(): mapOfFuncs.find(*name_)->second->getFather();
                   string tmp_func = funcName;
                   while (funcName != tmp)
                   {
                       funcName = mapOfFuncs.find(funcName)->second->getFather();
                       d++;
                   }
                   funcName = tmp_func;

                   if (mapOfFuncs.find(*name_)->second->isParameter_ == 1)
                   {
                       os << "lda " << lda_counter << " " << map.find(*name_)->second->getHead()->address_ << endl;
                       os << "movs 2" << endl;
                       cout << "b cupCounter = " << cupCounter << endl;
                       cupCounter += 2;
                       cout << "a cupCounter = " << cupCounter << endl;
                   }
                   else
                   {
                       cout << "b cupCounter = " << cupCounter << endl;
                       cupCounter += 2;
                       cout << "a cupCounter = " << cupCounter << endl;
                       os << "ldc " << *name_ << endl;
                       os << "lda " << d << " 0" << endl;
                   }
               }
               else
               {
                   if (mapOfFuncs.find(*name_) == mapOfFuncs.end() && map.find(*name_)->second->getHead()->size_ > 1)
                   {
                       sizeOfMovs =  map.find(*name_)->second->getHead()->size_;
                       flagMovs = 1;
                       cout << "b cupCounter = " << cupCounter << endl;
                       cout << "a cupCounter = " << cupCounter << endl;
                   }
                   //cupCounter += map.find(*name_)->second->getHead()->size_;
               }
//               if(mapOfFuncs.find(funCall)->second->getMap().find(tmp)->second->getHead()->byValOrbyRef_ == 0)
//               {
//                   os << "ind2" << endl;
//               }
               //paraIndex++;
           }
           if(mapOfFuncs.find(*name_) == mapOfFuncs.end() && map.find(*name_)->second->getHead()->byValOrbyRef_ == 1)
           {
               
               os << "ind" << endl;
           }
           cout << "end of idetype" << endl;
           lda_counter = 0;
           //        }
           //os << "func_is_parameter = " << func_is_parameter << endl;
           //        else if(callingFunc)
           //        {
           //            //os << "callingFunc " << callingFunc << endl;
           //            int depth = 0;
           //            if(mapOfFuncs.find(*name_) != mapOfFuncs.end())
           //            {
           //                cupCounter += 2;
           //                //                    cout << "bitch1" << endl;
           //                //                    for(int i = 0 ; i < mapOfFuncs.find(*name_)->second->getVec().size(); i++)
           //                //                    {
           //                //                        string str = mapOfFuncs.find(*name_)->second->getVec()[i];
           //                //                        cout << "b cupCounter = " << cupCounter << endl;
           //                //                        cupCounter += mapOfFuncs.find(*name_)->second->getMap().find(str)->second->getHead()->size_;
           //                //                        cout << "a cupCounter = " << cupCounter << endl;
           //                //                    }
           //
           //            }
           //            int j = 0, flag1 = 1;
           //            while (j < mapOfFuncs.find(funcName)->second->getVec().size() && flag1)
           //            {
           //                cout << "bitch2" << endl;
           //                if(mapOfFuncs.find(funcName)->second->getVec()[j] == *name_)
           //                {
           //                    flag1 = 0;
           //                }
           //                j++;
           //            }
           //            if(!flag1)
           //            {   string strr = funcName;
           //
           //                while(mapOfFuncs.find(*name_)->second->getFather() != strr)
           //                {
           //                    depth++;
           //                    strr = mapOfFuncs.find(strr)->second->getFather();
           //                }
           //                os << "lda " << depth <<  mapOfFuncs.find(funcName)->second->getMap().find(*name_)->second->getHead()->address_ << endl;
           //                os << "moves " << 2 << endl;
           //            }
           //            else
           //            {
           //                cout << "bitch3" << endl;
           //                os << "ldc " << *name_ << endl;
           //                cout << "name = " << *name_ << endl;
           //                cout << "funcName = " << funcName << endl;
           //                string s = funcName;
           //                while (s != mapOfFuncs.find(*name_)->second->getFather())
           //                {
           //                    cout << "before s = " << s << endl;
           //                    s = mapOfFuncs.find(s)->second->getFather();
           //                    cout << "after s = " << s << endl;
           //                    depth++;
           //                }
           //                os << "lda2 " << depth << " 0" << endl;
           //            }
           //        }
       }
        if(retValue && is_func && funcName == *name_)
        {
            os << "lda 0 0" << endl;
        }
        lda_counter = 0;
        
    }
    virtual Object * clone () const { return new IdeType(*this);}

private:
    string * name_;
};

class ArrayType : public Type {
    public :
    ArrayType (int l,int u, Object * type) : low_(l),up_(u),type_(type)  { assert(type_);}

    ArrayType(const ArrayType& a) : low_(a.low_), up_(a.up_){
        type_ = a.type_->clone();
    }

    virtual ~ArrayType () {
        if (type_) delete type_;
    }

    void print (ostream& os) {
        os<<"Node name : ArrayType: low bound is: "<<low_<<", up bound is: "<<up_<<endl;
        assert(type_);
        type_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(type_);
        in_array_type = 1;
        d_counter *= (up_ - low_ + 1);
        temp_low.push_back(low_);
        temp_d.push_back(up_ - low_ + 1);
        cout << "START OF ARRAY TYPE pcodeGen" << endl;
        type_->pcodegen(os);
        cout << "END OF ARRAY TYPE pcodeGen" << endl;
    }
    virtual Object * clone () const { return new ArrayType(*this);}

private:
    Object * type_;
    int low_,up_;
};

class RecordType : public Type {
    public :
    RecordType (Object * record_list) : record_list_(record_list)  { assert(record_list_);}

    RecordType(const RecordType& y){
        record_list_ = y.record_list_->clone();
    }

    virtual ~RecordType () {
        if (record_list_) delete record_list_;
    }

    void print (ostream& os) {
        os<<"Node name : RecordType"<<endl;
        assert(record_list_);
        record_list_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(record_list_);
        in_record_type = 1;
        rec_temp_name = temp_name;
        rec_start_address = address_counter;
        cout << "START OF RECORD TYPE pcodeGen" << endl;
        record_list_->pcodegen(os);
        cout << "END OF RECORD TYPE pcodeGen" << endl;
    }
    virtual Object * clone () const { return new RecordType(*this);}

private:
    Object * record_list_;
};


class AddressType : public Type {
    public :
    AddressType (Object * type) : type_(type)  { assert(type_);}

    AddressType(const AddressType& t){
        type_ = t.type_->clone();
    }

    virtual ~AddressType () {
        if (type_) delete type_;
    }

    void print (ostream& os) {
        os<<"Node name : AddressType"<<endl;
        assert(type_);
        type_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(type_);
        in_address_type = 1;
        cout << "START OF ADDRESS TYPE pcodeGen" << endl;
        type_->pcodegen(os);
        cout << "END OF ADDRESS TYPE pcodeGen" << endl;
    }
    virtual Object * clone () const { return new AddressType(*this);}

private:
    Object * type_;
};


class Declaration : public Object {
};

class VariableDeclaration : public Declaration {
public:
    VariableDeclaration (Object * type, const char * str) : type_(type){
        assert(type_);
        name_ = new string(str);
    }

    VariableDeclaration(const VariableDeclaration& p){
        type_ = p.type_->clone();
        name_ = new string(*p.name_);
    }

    virtual ~VariableDeclaration () {
        if (type_) delete type_;
        delete name_;
    }

    void print (ostream& os) {
        os<<"Node name : VariableDeclaration. Var name is: "<<*name_<<endl;
        assert(type_);
        type_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(type_);

        creating_ide = 1;
        temp_name = *name_;
        cout << "start pcodegen of VARIABLE" << endl;
        type_->pcodegen(os);
        
        cout << "END pcodegen of VARIABLE" << endl;
        temp_name = *name_;
        creating_ide = 0;
        Linkedlist* temp = new Linkedlist();
        //cout  << "@@@@@@@@@@@ rec_start_address in varDECPCODEGEN = " << rec_start_address <<endl;
        if (in_record_type && *name_ == rec_temp_name)
        {
            temp->insertNode(0, temp_name, rec_start_address, address_counter-rec_start_address, address_counter-rec_start_address, -1, "",-1);
            vector<string>::iterator itr = pointers_in_record.begin();
            while (itr != pointers_in_record.end())
            {
                mapOfHeads.find(*itr)->second->getHead()->sizeOfTYPE = temp->getHead()->sizeOfTYPE;
                mapOfHeads.find(*itr)->second->getHead()->sizeOfTypeName = temp->getHead()->name_;
                itr++;
            }
            //ssp += address_counter-rec_start_address;
            pointers_in_record.clear();
            in_record_type = 0;
            rec_start_address = -1;
        }
        else if(in_array_type)
        {
            int y;
            if (rec_start_address == -1)
            {
                y = rec_start_address;
            }
            else
            {
                y = address_counter-rec_start_address;
            }
            temp->insertNode(0, temp_name, address_counter, d_counter*sizeOfType, sizeOfType, y, sizeOfTname,-1);
            vector<int>::iterator itr1 = temp_d.begin();
            vector<int>::iterator itr2 = temp_low.begin();
            int i = 0;
            while (i < temp_d.size())
            {
                temp->getHead()->sizesOfArrays.push_back(itr1[i]);
                i++;
            }
            i = 0;
            while (i < temp_low.size())
            {
                temp->getHead()->low_counter.push_back(itr2[i]);
                i++;
            }
            temp_d.clear();
            temp_low.clear();
            in_array_type = 0;
            address_counter += d_counter*sizeOfType;
            ssp += d_counter*sizeOfType;
            d_counter = 1;
            sizeOfType = 1;
        }
        else if(in_address_type)
        {
            int y;
            if (rec_start_address == -1)
            {
                y = rec_start_address;
            }
            else
            {
                y = address_counter-rec_start_address;
            }
            temp->insertNode(0, temp_name, address_counter, 1, sizeOfType, y, sizeOfTname, -1);
            address_counter++;
            ssp++;
            in_address_type = 0;
            sizeOfType = 1;
        }
        else
        {
            int y;
            if (rec_start_address == -1)
            {
                y = rec_start_address;
            }
            else
            {
                y = address_counter-rec_start_address;
            }
            if(sizeOfType == 1 )
            {
                arrayRefName = "Fixed";
            }
            temp->insertNode(0, *name_, address_counter, sizeOfType, sizeOfType, y, arrayRefName, -1);
            address_counter += sizeOfType;
            ssp += sizeOfType;
            sizeOfType = 1;
        }
//        if(pro_func_flag)
//        {
//            //mapOfHeads.insert(pair<string, Linkedlist*>(*name_, temp));
//            func* tempFunc = mapOfFuncs.find(funcName)->second;
//            tempFunc->getMap().insert(pair<string, Linkedlist*>(*name_, temp));
//        }
//        if(program_flag)
//        {
//
//            mapOfProgram.insert(pair<string, Linkedlist*>(*name_, temp));
//        }
        //cout << "variable declartion funcname is = " << funcName << ", name = " << *name_ << endl;
        mapOfHeads.insert(pair<string, Linkedlist*>(*name_, temp));
        //mapOfFuncs.find(funcName)->second->getMap().insert(pair<string, Linkedlist*>(*name_, temp));
        //cout << "dada = " << mapOfFuncs.find(funcName)->second->getMap().find(*name_)->second->getHead()->name_ << endl;
        
        cout << "@@@@@@@@@@@@@@@@@ var dec nameof func = " << funcName << "var is = " << *name_ << endl;
    }
    virtual Object * clone () const { return new VariableDeclaration(*this);}

private:
    Object * type_;
    string * name_;
};

class Parameter : public Object {
    public :
    Parameter (Object * type, const char * name) : type_(type){
        assert(type_);
        cout << "CONS of Paramter" << endl;
        name_ = new string(name);
    }

    Parameter(const Parameter& p){
        type_ = p.type_->clone();
        cout << "CONS of Paramter" << endl;
        name_ = new string(*p.name_);
    }

    virtual ~Parameter () {
        if (type_) delete type_;
        delete name_;
    }

    void print (ostream& os) {
        printWayOfPassing(os);
        os<<"Parameter name :" <<*name_<<endl;
        assert(type_);
        type_->print(os);
    }
    void pcodegen(ostream& os) {
        printWayOfPassing(os);
        assert(type_);
        cout << "start pcodegen of PARA" << endl;
        creating_ide = 1;
        temp_name = *name_;
//        int tempfunc = is_func;
//        int tempPro = is_pro;
//        int tempProgr = program_flag;
        type_->pcodegen(os);
        int x;
        if(byRef)
        {
            x = 1;
            byRef = 0;
        }
        else
        {
            x = 0;
        }
        
        
        cout << "in parameter name = " << *name_ << endl;
        cout << "byref = " << x << endl;
        temp_name = *name_;
        creating_ide = 0;
        Linkedlist* temp = new Linkedlist();
        func* tmp = NULL;
        //cout  << "@@@@@@@@@@@ rec_start_address in varDECPCODEGEN = " << rec_start_address <<endl;
        if (in_record_type && *name_ == rec_temp_name)
        {
            temp->insertNode(0, temp_name, rec_start_address, address_counter-rec_start_address, address_counter-rec_start_address, -1, "",-1);
            vector<string>::iterator itr = pointers_in_record.begin();
            
            while (itr != pointers_in_record.end())
            {
                mapOfHeads.find(*itr)->second->getHead()->sizeOfTYPE = temp->getHead()->sizeOfTYPE;
                mapOfHeads.find(*itr)->second->getHead()->sizeOfTypeName = temp->getHead()->name_;
                itr++;
            }
            //cout << "here is unagi1" << endl;
            pointers_in_record.clear();
            in_record_type = 0;
            rec_start_address = -1;
        }
        else if(in_array_type)
        {
            int y;
            if (rec_start_address == -1)
            {
                y = rec_start_address;
            }
            else
            {
                y = address_counter-rec_start_address;
            }
            temp->insertNode(0, temp_name, address_counter, d_counter*sizeOfType, sizeOfType, y, sizeOfTname, -1);
            vector<int>::iterator itr1 = temp_d.begin();
            vector<int>::iterator itr2 = temp_low.begin();
            int i = 0;
            while (i < temp_d.size())
            {
                temp->getHead()->sizesOfArrays.push_back(itr1[i]);
                i++;
            }
            i = 0;
            while (i < temp_low.size())
            {
                temp->getHead()->low_counter.push_back(itr2[i]);
                i++;
            }
            temp_d.clear();
            temp_low.clear();
            in_array_type = 0;
            address_counter += d_counter*sizeOfType;
            ssp += d_counter*sizeOfType;
            d_counter = 1;
            sizeOfType = 1;
        }
        else if(in_address_type)
        {
            int y;
            if (rec_start_address == -1)
            {
                y = rec_start_address;
            }
            else
            {
                y = address_counter-rec_start_address;
            }
            temp->insertNode(0, temp_name, address_counter, 1, sizeOfType, y, sizeOfTname, -1);
            address_counter++;
            ssp++;
            in_address_type = 0;
            sizeOfType = 1;
        }
        else if (func_is_parameter)
        {
            int s = 0;
            func* tmp1 = mapOfFuncs.find(func_Para_name)->second;
            for(int i = 0; i <tmp1->getVec().size(); i++ )
            {
                s += tmp1->getMap().find(tmp1->getVec()[i])->second->getHead()->size_;
            }
            tmp = new func(*name_, funcName,tmp1->getMap(),tmp1->getVec(), 1);
            mapOfFuncs.insert(pair<string, func*>(*name_, tmp));
            func_is_parameter = 0;
            temp->insertNode(0, *name_, address_counter, 2, 1, -1, funcName, -1);
            //cout << "name = " << *name_<<" temp size = " << temp->getHead()->size_ << endl;;
            int sum = 0;
//            for(int i = 0 ; i < mapOfFuncs.find(*name_)->second->getVec().size(); i++)
//            {
//                string str = mapOfFuncs.find(*name_)->second->getVec()[i];
//                sum += mapOfFuncs.find(*name_)->second->getMap().find(str)->second->getHead()->size_;
//            }
            address_counter += 2;
            ssp += 2;
        }
        else
        {
            int y;
            if (rec_start_address == -1)
            {
                y = rec_start_address;
            }
            else
            {
                //os << "111here is unagi" << endl;
                y = address_counter-rec_start_address;
            }
            if(sizeOfType == 1 )
            {
                arrayRefName = "Fixed";
            }
            else
            {
                x = -1;
            }
            //os << "name: "<< *name_ <<"address_counter-rec_start_address = " << sizeOfType << endl;
            //os << "here is unagi" << endl;
            temp->insertNode(0, *name_, address_counter, sizeOfType, sizeOfType, y, arrayRefName, x);
            address_counter += sizeOfType;
            ssp += sizeOfType;
            sizeOfType = 1;
        }
        mapOfHeads.insert(pair<string, Linkedlist*>(*name_, temp));
        //cout << "x = " << mapOfHeads.find(*name_)->second->getHead()->byValOrbyRef_ << endl;
        parameters.push_back(*name_);
        cout << "END pcodegen of PARA" << endl;
    }
protected:
    virtual void printWayOfPassing (ostream& os) const = 0;

private:
    Object * type_;
    string * name_;
};

class ByReferenceParameter : public Parameter {
    public :
    ByReferenceParameter (Object * type, const char * name) : Parameter (type,name) {}
    virtual Object * clone () const { return new ByReferenceParameter(*this);}
protected:
    void printWayOfPassing (ostream& os) const{
        
        byRef = 1;
        //os<<"Node name : ByReferenceParameter ";
    }
};

class ByValueParameter : public Parameter {
    public :
    ByValueParameter (Object * type, const char * name) : Parameter(type,name) {}
    virtual Object * clone () const { return new ByValueParameter(*this);}
protected:
    void printWayOfPassing (ostream& os) const{
        //os<<"Node name : ByValueParameter ";
        byRef = 0;
    }
};

class ParameterList : public Object {
    public :
    ParameterList (Object * formal) : formal_(formal),  formal_list_(NULL) { assert(formal_);}
    ParameterList (Object * formal, Object * formal_list) : formal_(formal), formal_list_(formal_list) {assert(formal_ && formal_list_);}

    ParameterList(const ParameterList& pl){
        formal_ = pl.formal_->clone();
        formal_list_ = pl.formal_list_->clone();
    }

    virtual ~ParameterList () {
        if (formal_) delete formal_;
        if (formal_list_) delete formal_list_;
    }

    void print (ostream& os) {
        os<<"Node name : ParameterList"<<endl;
        assert(formal_);
        formal_->print(os);
        
        if (formal_list_){
            formal_list_->print(os);
        }
    }
    void pcodegen(ostream& os) {
        
        assert(formal_);
        if(is_pro || is_func || program_flag)
        {
            mapOfFuncs.find(funcName)->second->setManp(mapOfHeads);
            mapOfHeads.clear();
            os << funcName << ":" << endl;
            os << "ssp " << ssp << endl;
            os << "sep 50" << endl;
            cout << funcName << ":" << endl;
            cout << "ssp " << ssp << endl;
            ssp = 5;
            address_counter = 5;
            os << "ujp " << funcName << "_begin" << endl;
            cout << "ujp " << funcName << "_begin" << endl;
            is_pro = 0;
            is_func = 0;
            program_flag = 0;
        }
        formal_->pcodegen(os);
        cout << "start pcodegen of PARALIST" << endl;
        if (formal_list_) {
            formal_list_->pcodegen(os);
        }

        cout << "END pcodegen of PARALIST" << endl;
    }
    virtual Object * clone () const { return new ParameterList(*this);}

private:
    Object * formal_;
    Object * formal_list_;
};

class FunctionDeclaration : public Declaration {
    public :
    FunctionDeclaration (Object * type, Object * block, const char * name) : type_(type), block_(block), formal_list_(NULL) {
        assert(type_ && block_);
        name_ = new string(name);
        cout << "cons' OF FUNC" << endl;
    }

    FunctionDeclaration (Object * type, Object * formal_list, Object * block,  const char * name) : type_(type), formal_list_(formal_list),block_(block) {
        assert(type_ && formal_list_ && block_ );
        name_ = new string(name);
    }

    virtual ~FunctionDeclaration () {
        if (type_) delete type_;
        if (block_) delete block_;
        if (formal_list_) delete formal_list_;
        if (name_) delete name_;
    }

    FunctionDeclaration(const FunctionDeclaration& fd){
        type_ = fd.type_->clone();
        block_ = fd.block_->clone();
        formal_list_ = fd.formal_list_->clone();
        name_ = new string(*fd.name_);
    }

    void print (ostream& os) {
        os<<"Node name : FunctionDeclaration. Func name is: "<< *name_<<endl;
        assert(type_ && block_);
        type_->print(os);
        if (formal_list_){
            formal_list_->print(os);
        }
        block_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(type_ && block_);
        type_->pcodegen(os);
        if (formal_list_) {
            formal_list_->pcodegen(os);
        }
        cout << "start pcodegen of FUNC" << endl;
        int temp_program = program_flag;
        program_flag = 0;
        int temp_is_func = is_func;
        is_func = 1;
        last_func = 1;
        func* temp = new func(*name_, nameOfFather, mapOfHeads, parameters,0);
        parameters.clear();
        mapOfFuncs.insert(pair<string, func*>(*name_, temp)); // insert symbol table of function
        string temp_funcName = funcName;
        cout << "before  = " << funcName << endl;
        string temp_father = nameOfFather;
        funcName = *name_;
        cout << "before  = " << funcName << endl;
        nameOfFather = *name_;
        int temp_pro_func_flag = pro_func_flag;
        pro_func_flag = 1;
//        os << *name_ << ":" << endl;
//        os << "ssp " << ssp << endl;
//        cout << *name_ << ":" << endl;
//        cout << "ssp " << ssp << endl;
//        ssp = 5;
        block_->pcodegen(os);
        os << "retf" << endl;
        funcName = temp_funcName;
        cout << "after  = " << funcName << endl;
        pro_func_flag = temp_pro_func_flag;
        nameOfFather = temp_father;
        is_func = temp_is_func;
        program_flag = temp_program;
        cout << "END pcodegen of FUNC" << endl;
    }
    virtual Object * clone () const { return new FunctionDeclaration(*this);}

private:
    Object * type_;
    Object * block_;
    Object * formal_list_;
    string * name_;
};

class ProcedureDeclaration : public Declaration {
    public :
    ProcedureDeclaration (Object * block, const char * name) : formal_list_(NULL), block_(block) {
        assert(block_);
        name_ = new string(name);
        cout << "cons' OF PRO" << endl;
    }

    ProcedureDeclaration (Object * formal_list, Object * block, const char * name) : formal_list_(formal_list),block_(block)  {
        assert(formal_list_ && block_);
        name_ = new string(name);
        cout << "cons' OF PRO" << endl;
    }

    virtual ~ProcedureDeclaration () {
        if (block_) delete block_;
        if (formal_list_) delete formal_list_;
        if (name_) delete name_;
    }

    ProcedureDeclaration(const ProcedureDeclaration& pd){
        block_ = pd.block_->clone();
        formal_list_ = pd.formal_list_->clone();
        name_ = new string(*pd.name_);
    }

    void print (ostream& os) {
        os<<"Node name : ProcedureDeclaration. Proc name is: "<< *name_<<endl;
        assert(block_);
        if (formal_list_){
            formal_list_->print(os);
        }
        block_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(block_);
        if (formal_list_) {
            formal_list_->pcodegen(os);
        }
        cout << "start pcodegen of PRO" << endl;
        func* temp = new func(*name_, nameOfFather, mapOfHeads, parameters,0);
        parameters.clear();
        cout << "nameOffather = " << nameOfFather << endl;
        cout << "name = " << *name_ << endl;
        cout << "size of map = " << temp->getMap().size() << endl;
        //cout << "is = " << temp->getMap().begin()->second->getHead()->name_ << endl;
        //cout << "is = " << temp->getMap().cbegin()->first << endl;
        mapOfFuncs.insert(pair<string, func*>(*name_, temp)); // insert symbol table of function
        cout << "size of map = " << mapOfFuncs.size();
//      map<string, func*> :: const_iterator it = mapOfFuncs.begin();
//        for (; it != mapOfFuncs.end(); ++it)
//        {
//            map<string, Linkedlist*> :: const_iterator *it2 = it->second->getMap().begin();
//            for (; it2 != ; ) {
//
//            }
//        }
//
        int temp_program = program_flag;
        program_flag = 0;
        string temp_funcName = funcName;
        cout << "before  = " << funcName << endl;
        string temp_father = nameOfFather;
        funcName = *name_;
        cout << "before  = " << funcName << endl;
        nameOfFather = *name_;
        int temp_pro_func_flag = pro_func_flag;
        pro_func_flag = 1;
//        os << *name_ << ":" << endl;
//        os << "ssp " << ssp << endl;
//        cout << *name_ << ":" << endl;
//        cout << "ssp " << ssp << endl;
//        ssp = 5;
        int temp_is_pro = is_pro;
        is_pro = 1;
        last_func = 1;
//        os << "ujp " << *name_ << "_begin" << endl;
//        cout << "ujp " << *name_ << "_begin" << endl;
        block_->pcodegen(os);
        
        os << "retp" << endl;
        
        is_pro = temp_is_pro;
        funcName = temp_funcName;
        cout << "after  = " << funcName << endl;
        pro_func_flag = temp_pro_func_flag;
        nameOfFather = temp_father;
        
        program_flag = temp_program;
        cout << "END pcodegen of PRO" << endl;
    }
    virtual Object * clone () const { return new ProcedureDeclaration(*this);}

private:
    Object * block_;
    Object * formal_list_;
    string * name_;
};

class DeclarationList : public Object {
    public :
    DeclarationList (Object * decl) : decl_(decl), decl_list_(NULL) { assert(decl_);}
    DeclarationList (Object * decl_list, Object * decl) : decl_list_(decl_list),decl_(decl)  {assert(decl_list_ && decl);}

    DeclarationList(const DeclarationList& dl){
        decl_ = dl.decl_->clone();
        decl_list_ = dl.decl_list_->clone();
    }

    virtual ~DeclarationList () {
        if (decl_) delete decl_;
        if (decl_list_) delete decl_list_;
    }

    void print (ostream& os) {
        os<<"Node name : DeclarationList"<<endl;
        if (decl_list_){
            decl_list_->print(os);
        }
        assert(decl_);
        decl_->print(os);
    }
    void pcodegen(ostream& os) {
        if (decl_list_) {
            decl_list_->pcodegen(os);
        }
        assert(decl_);
        cout << "START of pcodegen OF DECLIST" << endl;
        decl_->pcodegen(os);
        cout << "END of pcodegen OF DECLIST" << endl;
    }
    virtual Object * clone () const { return new DeclarationList(*this);}

private:
    Object * decl_;
    Object * decl_list_;
};

class Block : public Object {
    public :
    Block (Object * stat_seq) : stat_seq_(stat_seq), decl_list_(NULL)  { assert(stat_seq_);}
    Block (Object * decl_list, Object * stat_seq) : decl_list_(decl_list), stat_seq_(stat_seq)  {assert(decl_list_ && stat_seq_);}

    Block(const Block& b){
        decl_list_ = b.decl_list_->clone();
        stat_seq_ = b.stat_seq_->clone();
    }

    virtual ~Block () {
        if (stat_seq_) delete stat_seq_;
        if (decl_list_) delete decl_list_;
    }

    void print (ostream& os) {
        os<<"Node name : Begin"<<endl;
        if (decl_list_){
            decl_list_->print(os);
        }
        assert(stat_seq_);
        stat_seq_->print(os);
    }
    void pcodegen(ostream& os) {
        if (decl_list_) {
            cout << "ggfdsf" << endl;
            decl_list_->pcodegen(os);
        }
        cout << "heeeeere" << endl;
        cout << "now func " << funcName << endl;
        assert(stat_seq_);
        if(last_func)
        {
            last_func = 0;
            os << funcName << ":" << endl;
            os << "ssp " << ssp << endl;
            os << "sep 50" << endl;
            cout << funcName << ":" << endl;
            cout << "ssp " << ssp << endl;
            ssp = 5;
            address_counter = 5;
            os << "ujp " << funcName << "_begin" << endl;
            cout << "ujp " << funcName << "_begin" << endl;
            mapOfFuncs.find(funcName)->second->setManp(mapOfHeads);
            mapOfHeads.clear();
        }
        os << funcName << "_begin:" << endl;
        stat_seq_->pcodegen(os);
        cout << "END pcodegen of BLOCK" << endl;
    }

    virtual Object * clone () const { return new Block(*this);}

private:
    Object * decl_list_;
    Object * stat_seq_;
};

class Program : public Object {
    public :
    Program (Object * block, const char * str) : block_(NULL) {
        block_ = dynamic_cast<Block *>(block);
        assert(block_);
        name_ = new string(str);
    }

    Program(const Program& prog){
        block_ = dynamic_cast<Block *>(prog.block_->clone());
        assert(block_);
        name_ = new string(*prog.name_);
    }

    virtual ~Program () {
        if (block_) delete block_;
        delete name_;
    }

    void print (ostream& os) {
        os<<"Node name : Root/Program. Program name is: "<<*name_<<endl;
        assert(block_);
        block_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(block_);
        cout << "start pcodegen of PROGRAM" << endl;
        program_flag = 1;
        func* temp = new func(*name_, "NULL", mapOfHeads, parameters,0);
        mapOfFuncs.insert(pair<string, func*>(*name_, temp));
        nameOfFather = *name_;
        funcName = *name_;
//        os << *name_ << ":" << endl;
//        os << "ssp " << ssp << endl;
//        cout << *name_ << ":" << endl;
//        cout << "ssp " << ssp << endl;
//        ssp = 5;
//        os << "ujp " << *name_ << "_begin" << endl;
//        cout << "ujp " << *name_ << "_begin" << endl;
        block_->pcodegen(os);
        os << "stp" << endl;
        cout << "end pcodegen of PROGRAM" << endl;
    }
    virtual Object * clone () const { return new Program(*this);}

private:
    Block * block_;
    string * name_;
};





#endif //AST_H

