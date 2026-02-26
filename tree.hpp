/* tree.hpp.  Generated automatically by treecc */
#ifndef __yy_tree_hpp
#define __yy_tree_hpp
#line 3 "tree.tc"

    #include <iostream>
    #include <string>
    #include <unordered_map>
    
    using StdString = std::string;
    using VarTable = std::unordered_map<StdString, long>;
#line 13 "tree.hpp"

#include <new>

const int AstNode_kind = 1;
const int Expr_kind = 2;
const int BinaryExpr_kind = 3;
const int NumberExpr_kind = 9;
const int IdentifierExpr_kind = 10;
const int AddExpr_kind = 4;
const int SubExpr_kind = 5;
const int MulExpr_kind = 6;
const int DivExpr_kind = 7;
const int ModExpr_kind = 8;

class AstNode;
class Expr;
class BinaryExpr;
class NumberExpr;
class IdentifierExpr;
class AddExpr;
class SubExpr;
class MulExpr;
class DivExpr;
class ModExpr;

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
#line 52 "tree.hpp"
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

	virtual long evaluate(VarTable * vars) = 0;
	virtual StdString toString() = 0;

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

	virtual long evaluate(VarTable * vars) = 0;
	virtual StdString toString() = 0;

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~Expr();

};

class BinaryExpr : public Expr
{
protected:

	BinaryExpr(Expr * left, Expr * right);

public:

	Expr * left;
	Expr * right;

	virtual long evaluate(VarTable * vars) = 0;
	virtual StdString toString() = 0;

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~BinaryExpr();

};

class NumberExpr : public Expr
{
public:

	NumberExpr(long value);

public:

	long value;

	virtual long evaluate(VarTable * vars);
	virtual StdString toString();

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~NumberExpr();

};

class IdentifierExpr : public Expr
{
public:

	IdentifierExpr(StdString name);

public:

	StdString name;

	virtual long evaluate(VarTable * vars);
	virtual StdString toString();

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~IdentifierExpr();

};

class AddExpr : public BinaryExpr
{
public:

	AddExpr(Expr * left, Expr * right);

public:

	virtual long evaluate(VarTable * vars);
	virtual StdString toString();

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~AddExpr();

};

class SubExpr : public BinaryExpr
{
public:

	SubExpr(Expr * left, Expr * right);

public:

	virtual long evaluate(VarTable * vars);
	virtual StdString toString();

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~SubExpr();

};

class MulExpr : public BinaryExpr
{
public:

	MulExpr(Expr * left, Expr * right);

public:

	virtual long evaluate(VarTable * vars);
	virtual StdString toString();

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~MulExpr();

};

class DivExpr : public BinaryExpr
{
public:

	DivExpr(Expr * left, Expr * right);

public:

	virtual long evaluate(VarTable * vars);
	virtual StdString toString();

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~DivExpr();

};

class ModExpr : public BinaryExpr
{
public:

	ModExpr(Expr * left, Expr * right);

public:

	virtual long evaluate(VarTable * vars);
	virtual StdString toString();

	virtual int isA(int kind) const;
	virtual const char *getKindName() const;

protected:

	virtual ~ModExpr();

};



#endif
