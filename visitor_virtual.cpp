#include <iostream>
#include <vector>
using namespace std;

class Visitor;

class Node {
public:
    virtual void accept(Visitor&) = 0;
};

class Expr:public Node {
public:
    void accept(Visitor& v) override;
};
class Stmt:public Node {
public:
    void accept(Visitor& v) override; 
};

class Visitor {
public:
    virtual void accept(Expr&) = 0;
    virtual void accept(Stmt&) = 0;
};

void Expr::accept(Visitor& v) {
    v.accept(*this);
}
void Stmt::accept(Visitor& v) {
    v.accept(*this);
}

class Do1_visitor:public Visitor {
public:
    void accept(Expr&) override {
        cout << "do1 visitor to Expr" << endl;
    }
    void accept(Stmt&) override {
        cout << "do1 visitor to Stmt" << endl;
    }
};
class Do2_visitor:public Visitor {
public:
    void accept(Expr&) override {
        cout << "do2 visitor to Expr" << endl;
    }
    void accept(Stmt&) override {
        cout << "do2 visitor to Stmt" << endl;
    }
};

int main(int argc, char* argv[])
try
{
    Expr e;
    Stmt s;
    Do1_visitor do1;
    Do2_visitor do2;
    vector<pair<Node*, Visitor*>> vn {
        {&e,&do1},
        {&s,&do1},
        {&e,&do2},
        {&s,&do2},
    };
    for (auto p : vn)
        p.first->accept(*p.second);
    return 0;
}
catch (const std::exception &e)
{
    std::cerr << e.what() << std::endl;
    return 1;
}
catch (...)
{
    std::cerr << "Oops: unknown exception!\n";
    return 2;
}