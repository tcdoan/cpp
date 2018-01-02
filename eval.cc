// evaluate expression tree

#include <memory>
#include <iostream>
#include <exception>

using namespace std;

int valtab[127]; 

class Tree;

// abstract base Node class
class Node
{
protected:
  virtual int eval() const = 0;
  virtual void print (ostream& ) const = 0;
  virtual ~Node() {};
private:
  friend class Tree;  
  friend ostream& operator<<(ostream&, const Tree&);
};

class Tree
{
public:
  Tree(const Tree& tree) { p = tree.p; }
  Tree(int n);
  Tree(char id);
  Tree(char op, const Tree& operand);
  Tree(char op, const Tree& left, const Tree& right);
  void operator=(const Tree& t) { p = t.p; }
    
  int eval() const
  {
    return p->eval();
  }
  
private:
  shared_ptr<Node> p;
  friend class Node;
  friend ostream& operator<<(ostream&, const Tree&);
};

ostream& operator<<(ostream& os, const Tree& tree)
{
  tree.p -> print(os);
  return os;
}

class IntNode : public Node
{
private:
  friend class Tree;
  int eval() const { return n; }
  
  virtual void print (ostream& out) const
  {
    out << n;
  }
  
  int n;
  IntNode(int k) : n(k) {}
};

class IdNode : public Node
{
private:
  friend class Tree;
  int eval() const { return valtab[id]; }
  
  virtual void print (ostream& out) const
  {
    out << id;
  }
  
  char id;
  IdNode(char c) : id(c) {}
};

class UnaryNode : public Node
{
private:
  friend class Tree;
  int eval() const
  {
    switch(op)
      {
      case '-':
	return -operand.eval();
      case '+':
	return operand.eval();
      default:
	throw runtime_error("no operator found");
      }      
  }
  
  virtual void print (ostream& out) const
  {
    out << "(" << op << operand << ")";
  }
  
  char op;
  Tree operand;
  UnaryNode(char op, const Tree& operand) : op(op), operand(operand) {}
};

class BinaryNode : public Node
{
private:
  friend class Tree;
  int eval() const
  {
    switch(op)
      {
      case '-':
	return left.eval() - right.eval();
      case '+':
	return left.eval() + right.eval();
      case '*':
	return left.eval() * right.eval();
      default:	
	throw runtime_error("invalid operator found");
      }      
  }
  
  virtual void print (ostream& out) const
  {
    out << "(" << left << " " << op << " " << right << ")";
  }
  
  char op;
  Tree left;
  Tree right;
  BinaryNode(char op, const Tree& left, const Tree& right) : op(op), left(left), right(right) {}
};

Tree::Tree(int n) : p(new IntNode(n)) {}
Tree::Tree(char id) : p(new IdNode(id)) {}
Tree::Tree(char op, const Tree& operand) : p(new UnaryNode(op, operand)) {}
Tree::Tree(char op, const Tree& left, const Tree& right) : p(new BinaryNode(op, left, right)) {}

int main()
{
  valtab['A'] = 3; valtab['B'] = 4;
  cout << "A = 3,  B = 4" << endl;
    
  Tree t1 = Tree('*', Tree('-', 5), Tree('+', 'A', 4));
  Tree t2 = Tree('+', Tree('-', 'A', 1), Tree('+', t1, 'B'));
  cout << "t1 = " << t1 << endl;
  cout << "t2 = " << t2 << endl;
  cout << "t1 = " << t1.eval() << endl;
  cout << "t2 = " << t2.eval() << endl;    
}
