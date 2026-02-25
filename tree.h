/* tree.h.  Generated automatically by treecc */
#ifndef __yy_tree_h
#define __yy_tree_h
#line 3 "tree.tc"

#include <string>
using stdstring = std::string;
#line 9 "tree.h"

#include <new>

const int AstNode_kind = 1;
const int Expr_kind = 2;
const int BinaryExpr_kind = 3;
const int NumberExpr_kind = 5;
const int AddExpr_kind = 4;

class AstNode;
class Expr;
class BinaryExpr;
class NumberExpr;
class AddExpr;

class YYNODESTATE
{
public:

	YYNODESTATE();
	virtual ~YYNODESTATE();

#line 1 "cpp_skel.h"
private:

	struct YYNODESTATE_block *blocks__;
	struct YYNODESTATE_push *push_stack__;
	int used__;
#line 38 "tree.h"
private:

	static YYNODESTATE *state__;

public:

	static YYNODESTATE *getState()
		{
			if(state__) return state__;
			state__ = new YYNODESTATE();
			return state__;
		}

public:

	void *alloc(size_t);
	void dealloc(void *, size_t);
	int push();
	void pop();
	void clear();
	virtual void failed();
	virtual const char *currFilename() const;
	virtual long currLinenum() const;

};

class AstNode
{
protected:

	int kind__;
	const char *filename__;
	long linenum__;

public:

	int getKind() const { return kind__; }
	const char *getFilename() const { return filename__; }
	long getLinenum() const { return linenum__; }
	void setFilename(const char *filename) { filename__ = filename; }
	void setLinenum(long linenum) { linenum__ = linenum; }

	void *operator new(size_t);
	void operator delete(void *, size_t);

protected:

	AstNode();

public:

	virtual int evaluate() = 0;

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~AstNode();

};

class Expr : public AstNode
{
protected:

	Expr();

public:

	virtual int evaluate() = 0;

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~Expr();

};

class BinaryExpr : public Expr
{
protected:

	BinaryExpr(Expr * expr1, Expr * expr2);

public:

	Expr * expr1;
	Expr * expr2;

	virtual int evaluate() = 0;

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~BinaryExpr();

};

class NumberExpr : public Expr
{
public:

	NumberExpr(int value);

public:

	int value;

	virtual int evaluate();

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~NumberExpr();

};

class AddExpr : public BinaryExpr
{
public:

	AddExpr(Expr * expr1, Expr * expr2);

public:

	virtual int evaluate();

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~AddExpr();

};



#endif
