/* tree.cpp.  Generated automatically by treecc */
#line 12 "tree.tc"

     #include "tree.hpp"
    #include <iostream>
#line 7 "tree.cpp"

#include <cstddef>

#define YYNODESTATE_TRACK_LINES 1
#define YYNODESTATE_USE_ALLOCATOR 1
#line 1 "cpp_skel.cc"
/*
 * treecc node allocation routines for C++.
 *
 * Copyright (C) 2001  Southern Storm Software, Pty Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * As a special exception, when this file is copied by treecc into
 * a treecc output file, you may use that output file without restriction.
 */

#ifndef YYNODESTATE_BLKSIZ
#define	YYNODESTATE_BLKSIZ	2048
#endif

/*
 * Types used by the allocation routines.
 */
struct YYNODESTATE_block
{
	char data__[YYNODESTATE_BLKSIZ];
	struct YYNODESTATE_block *next__;

};
struct YYNODESTATE_push
{
	struct YYNODESTATE_push *next__;
	struct YYNODESTATE_block *saved_block__;
	int saved_used__;
};

/*
 * Initialize the singleton instance.
 */
#ifndef YYNODESTATE_REENTRANT
YYNODESTATE *YYNODESTATE::state__ = 0;
#endif

/*
 * Some macro magic to determine the default alignment
 * on this machine.  This will compile down to a constant.
 */
#define	YYNODESTATE_ALIGN_CHECK_TYPE(type,name)	\
	struct _YYNODESTATE_align_##name { \
		char pad; \
		type field; \
	}
#define	YYNODESTATE_ALIGN_FOR_TYPE(type)	\
	offsetof(_YYNODESTATE_align_##type, field)
#define	YYNODESTATE_ALIGN_MAX(a,b)	\
	((a) > (b) ? (a) : (b))
#define	YYNODESTATE_ALIGN_MAX3(a,b,c) \
	(YYNODESTATE_ALIGN_MAX((a), YYNODESTATE_ALIGN_MAX((b), (c))))
YYNODESTATE_ALIGN_CHECK_TYPE(int, int);
YYNODESTATE_ALIGN_CHECK_TYPE(long, long);
#if defined(WIN32) && !defined(__CYGWIN__)
YYNODESTATE_ALIGN_CHECK_TYPE(__int64, long_long);
#else
YYNODESTATE_ALIGN_CHECK_TYPE(long long, long_long);
#endif
YYNODESTATE_ALIGN_CHECK_TYPE(void *, void_p);
YYNODESTATE_ALIGN_CHECK_TYPE(float, float);
YYNODESTATE_ALIGN_CHECK_TYPE(double, double);
#define	YYNODESTATE_ALIGNMENT	\
	YYNODESTATE_ALIGN_MAX( \
			YYNODESTATE_ALIGN_MAX3	\
			(YYNODESTATE_ALIGN_FOR_TYPE(int), \
		     YYNODESTATE_ALIGN_FOR_TYPE(long), \
			 YYNODESTATE_ALIGN_FOR_TYPE(long_long)), \
  	     YYNODESTATE_ALIGN_MAX3 \
		 	(YYNODESTATE_ALIGN_FOR_TYPE(void_p), \
			 YYNODESTATE_ALIGN_FOR_TYPE(float), \
			 YYNODESTATE_ALIGN_FOR_TYPE(double)))

/*
 * Constructor for YYNODESTATE.
 */
YYNODESTATE::YYNODESTATE()
{
	/* Initialize the allocation state */
	blocks__ = 0;
	push_stack__ = 0;
	used__ = 0;

#ifndef YYNODESTATE_REENTRANT
	/* Register this object as the singleton instance */
	if(!state__)
	{
		state__ = this;
	}
#endif
}

/*
 * Destructor for YYNODESTATE.
 */
YYNODESTATE::~YYNODESTATE()
{
	/* Free all node memory */
	clear();

#ifndef YYNODESTATE_REENTRANT
	/* We are no longer the singleton instance */
	if(state__ == this)
	{
		state__ = 0;
	}
#endif
}

#ifdef YYNODESTATE_USE_ALLOCATOR

/*
 * Allocate a block of memory.
 */
void *YYNODESTATE::alloc(size_t size__)
{
	struct YYNODESTATE_block *block__;
	void *result__;

	/* Round the size to the next alignment boundary */
	size__ = (size__ + YYNODESTATE_ALIGNMENT - 1) &
				~(YYNODESTATE_ALIGNMENT - 1);

	/* Do we need to allocate a new block? */
	block__ = blocks__;
	if(!block__ || (used__ + size__) > YYNODESTATE_BLKSIZ)
	{
		if(size__ > YYNODESTATE_BLKSIZ)
		{
			/* The allocation is too big for the node pool */
			return (void *)0;
		}
		block__ = new YYNODESTATE_block;
		if(!block__)
		{
			/* The system is out of memory.  The programmer can
			   inherit the "failed" method to report the
			   out of memory state and/or abort the program */
			failed();
			return (void *)0;
		}
		block__->next__ = blocks__;
		blocks__ = block__;
		used__ = 0;
	}

	/* Allocate the memory and return it */
	result__ = (void *)(block__->data__ + used__);
	used__ += size__;
	return result__;
}

/*
 * Deallocate a block of memory.
 */
void YYNODESTATE::dealloc(void *ptr__, size_t size__)
{
	/* Nothing to do for this type of node allocator */
}

/*
 * Push the node allocation state.
 */
int YYNODESTATE::push()
{
	struct YYNODESTATE_block *saved_block__;
	int saved_used__;
	struct YYNODESTATE_push *push_item__;

	/* Save the current state of the node allocation pool */
	saved_block__ = blocks__;
	saved_used__ = used__;

	/* Allocate space for a push item */
	push_item__ = (struct YYNODESTATE_push *)
			alloc(sizeof(struct YYNODESTATE_push));
	if(!push_item__)
	{
		return 0;
	}

	/* Copy the saved information to the push item */
	push_item__->saved_block__ = saved_block__;
	push_item__->saved_used__ = saved_used__;

	/* Add the push item to the push stack */
	push_item__->next__ = push_stack__;
	push_stack__ = push_item__;
	return 1;
}

/*
 * Pop the node allocation state.
 */
void YYNODESTATE::pop()
{
	struct YYNODESTATE_push *push_item__;
	struct YYNODESTATE_block *saved_block__;
	struct YYNODESTATE_block *temp_block__;

	/* Pop the top of the push stack */
	push_item__ = push_stack__;
	if(push_item__ == 0)
	{
		saved_block__ = 0;
		used__ = 0;
	}
	else
	{
		saved_block__ = push_item__->saved_block__;
		used__ = push_item__->saved_used__;
		push_stack__ = push_item__->next__;
	}

	/* Free unnecessary blocks */
	while(blocks__ != saved_block__)
	{
		temp_block__ = blocks__;
		blocks__ = temp_block__->next__;
		delete temp_block__;
	}
}

/*
 * Clear the node allocation pool completely.
 */
void YYNODESTATE::clear()
{
	struct YYNODESTATE_block *temp_block__;
	while(blocks__ != 0)
	{
		temp_block__ = blocks__;
		blocks__ = temp_block__->next__;
		delete temp_block__;
	}
	push_stack__ = 0;
	used__ = 0;
}

#endif /* YYNODESTATE_USE_ALLOCATOR */

/*
 * Default implementation of functions which may be overridden.
 */
void YYNODESTATE::failed()
{
}

#ifdef YYNODESTATE_TRACK_LINES

const char *YYNODESTATE::currFilename() const
{
	return (const char *)0;
}

long YYNODESTATE::currLinenum() const
{
	return 0;
}

#endif
#line 288 "tree.cpp"
void *AstNode::operator new(size_t size__)
{
	return YYNODESTATE::getState()->alloc(size__);
}

void AstNode::operator delete(void *ptr__, size_t size__)
{
	YYNODESTATE::getState()->dealloc(ptr__, size__);
}

AstNode::AstNode()
{
	this->kind__ = AstNode_kind;
	this->filename__ = YYNODESTATE::getState()->currFilename();
	this->linenum__ = YYNODESTATE::getState()->currLinenum();
}

AstNode::~AstNode()
{
	// not used
}

int AstNode::isA(int kind) const
{
	if(kind == AstNode_kind)
		return 1;
	else
		return 0;
}

const char *AstNode::getKindName() const
{
	return "AstNode";
}

Expr::Expr()
	: AstNode()
{
	this->kind__ = Expr_kind;
}

Expr::~Expr()
{
	// not used
}

int Expr::isA(int kind) const
{
	if(kind == Expr_kind)
		return 1;
	else
		return AstNode::isA(kind);
}

const char *Expr::getKindName() const
{
	return "Expr";
}

BinaryExpr::BinaryExpr(Expr * left, Expr * right)
	: Expr()
{
	this->kind__ = BinaryExpr_kind;
	this->left = left;
	this->right = right;
}

BinaryExpr::~BinaryExpr()
{
	// not used
}

int BinaryExpr::isA(int kind) const
{
	if(kind == BinaryExpr_kind)
		return 1;
	else
		return Expr::isA(kind);
}

const char *BinaryExpr::getKindName() const
{
	return "BinaryExpr";
}

NumberExpr::NumberExpr(long value)
	: Expr()
{
	this->kind__ = NumberExpr_kind;
	this->value = value;
}

NumberExpr::~NumberExpr()
{
	// not used
}

long NumberExpr::evaluate(VarTable * vars)
#line 74 "tree.tc"
{
    return value;
}
#line 391 "tree.cpp"

StdString NumberExpr::toString()
#line 110 "tree.tc"
{
    return std::to_string(value);
}
#line 398 "tree.cpp"

int NumberExpr::isA(int kind) const
{
	if(kind == NumberExpr_kind)
		return 1;
	else
		return Expr::isA(kind);
}

const char *NumberExpr::getKindName() const
{
	return "NumberExpr";
}

IdentifierExpr::IdentifierExpr(StdString name)
	: Expr()
{
	this->kind__ = IdentifierExpr_kind;
	this->name = name;
}

IdentifierExpr::~IdentifierExpr()
{
	// not used
}

long IdentifierExpr::evaluate(VarTable * vars)
#line 78 "tree.tc"
{
    auto it = vars->find(name);
    if (it == vars->end()) {
        std::cerr << "Error: Variable '" << name << "' no definida" << std::endl;
        return 0;
    }
    return it->second;
}
#line 435 "tree.cpp"

StdString IdentifierExpr::toString()
#line 114 "tree.tc"
{
    return name;
}
#line 442 "tree.cpp"

int IdentifierExpr::isA(int kind) const
{
	if(kind == IdentifierExpr_kind)
		return 1;
	else
		return Expr::isA(kind);
}

const char *IdentifierExpr::getKindName() const
{
	return "IdentifierExpr";
}

AddExpr::AddExpr(Expr * left, Expr * right)
	: BinaryExpr(left, right)
{
	this->kind__ = AddExpr_kind;
}

AddExpr::~AddExpr()
{
	// not used
}

long AddExpr::evaluate(VarTable * vars)
#line 44 "tree.tc"
{
    return left->evaluate(vars) + right->evaluate(vars);
}
#line 473 "tree.cpp"

StdString AddExpr::toString()
#line 90 "tree.tc"
{
    return left->toString() + " + " + right->toString();
}
#line 480 "tree.cpp"

int AddExpr::isA(int kind) const
{
	if(kind == AddExpr_kind)
		return 1;
	else
		return BinaryExpr::isA(kind);
}

const char *AddExpr::getKindName() const
{
	return "AddExpr";
}

SubExpr::SubExpr(Expr * left, Expr * right)
	: BinaryExpr(left, right)
{
	this->kind__ = SubExpr_kind;
}

SubExpr::~SubExpr()
{
	// not used
}

long SubExpr::evaluate(VarTable * vars)
#line 48 "tree.tc"
{
    return left->evaluate(vars) - right->evaluate(vars);
}
#line 511 "tree.cpp"

StdString SubExpr::toString()
#line 94 "tree.tc"
{
    return left->toString() + " - " + right->toString();
}
#line 518 "tree.cpp"

int SubExpr::isA(int kind) const
{
	if(kind == SubExpr_kind)
		return 1;
	else
		return BinaryExpr::isA(kind);
}

const char *SubExpr::getKindName() const
{
	return "SubExpr";
}

MulExpr::MulExpr(Expr * left, Expr * right)
	: BinaryExpr(left, right)
{
	this->kind__ = MulExpr_kind;
}

MulExpr::~MulExpr()
{
	// not used
}

long MulExpr::evaluate(VarTable * vars)
#line 52 "tree.tc"
{
    return left->evaluate(vars) * right->evaluate(vars);
}
#line 549 "tree.cpp"

StdString MulExpr::toString()
#line 98 "tree.tc"
{
    return left->toString() + " * " + right->toString();
}
#line 556 "tree.cpp"

int MulExpr::isA(int kind) const
{
	if(kind == MulExpr_kind)
		return 1;
	else
		return BinaryExpr::isA(kind);
}

const char *MulExpr::getKindName() const
{
	return "MulExpr";
}

DivExpr::DivExpr(Expr * left, Expr * right)
	: BinaryExpr(left, right)
{
	this->kind__ = DivExpr_kind;
}

DivExpr::~DivExpr()
{
	// not used
}

long DivExpr::evaluate(VarTable * vars)
#line 56 "tree.tc"
{
    long rightVal = right->evaluate(vars);
    if (rightVal == 0) {
        std::cerr << "Error: División por cero" << std::endl;
        return 0;
    }
    return left->evaluate(vars) / rightVal;
}
#line 592 "tree.cpp"

StdString DivExpr::toString()
#line 102 "tree.tc"
{
    return left->toString() + " / " + right->toString();
}
#line 599 "tree.cpp"

int DivExpr::isA(int kind) const
{
	if(kind == DivExpr_kind)
		return 1;
	else
		return BinaryExpr::isA(kind);
}

const char *DivExpr::getKindName() const
{
	return "DivExpr";
}

ModExpr::ModExpr(Expr * left, Expr * right)
	: BinaryExpr(left, right)
{
	this->kind__ = ModExpr_kind;
}

ModExpr::~ModExpr()
{
	// not used
}

long ModExpr::evaluate(VarTable * vars)
#line 65 "tree.tc"
{
    long rightVal = right->evaluate(vars);
    if (rightVal == 0) {
        std::cerr << "Error: Módulo por cero" << std::endl;
        return 0;
    }
    return left->evaluate(vars) % rightVal;
}
#line 635 "tree.cpp"

StdString ModExpr::toString()
#line 106 "tree.tc"
{
    return left->toString() + " % " + right->toString();
}
#line 642 "tree.cpp"

int ModExpr::isA(int kind) const
{
	if(kind == ModExpr_kind)
		return 1;
	else
		return BinaryExpr::isA(kind);
}

const char *ModExpr::getKindName() const
{
	return "ModExpr";
}

