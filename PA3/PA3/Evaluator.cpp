
#include "Evaluator.h"

#include "ast/expression.h"





/*
 * This skeleton currently only contains code to handle integer constants, print and read. 
 * It is your job to handle all of the rest of the L language.
 */





/*
 * Call this function to report any run-time errors
 * This will abort execution.
 */
void report_error(Expression* e, const string & s)
{
	cout << "Run-time error in expression " << e->to_value() << endl;
	cout << s << endl;
	exit(1);

}



Evaluator::Evaluator()
{
	sym_tab.push();
	c = 0;

}

Expression* Evaluator::eval_unop(AstUnOp* b)
{





	Expression* e = b->get_expression();
	Expression* eval_e = eval(e);

	if(b->get_unop_type() == PRINT) {
		if(eval_e->get_type() == AST_STRING) {
			AstString* s = static_cast<AstString*>(eval_e);
			cout << s->get_string() << endl;
		}
		else cout << eval_e->to_value() << endl;
		return AstInt::make(0);
	}
	
	if(b->get_unop_type() == HD) {
	  if(eval_e->get_type() == AST_LIST) {
	    AstList* l = static_cast<AstList*>(eval_e);
	     return l->get_hd();
	  }
	  //otherwise just return the value
	  else{
	  return eval_e;
	  }
	}
	
	
      if (b->get_unop_type() == TL){
	if(eval_e->get_type() == AST_LIST) {
	  AstList* l = static_cast<AstList*>(eval_e);
	  return l->get_tl();
	}
	//otherwise return nil
	else{
	  return AstNil::make();
	}
      }
      
      
      if (b->get_unop_type() == ISNIL){
	if(eval_e->get_type() == AST_NIL) {
	  return AstInt::make(1);
	}
	else{
	  return AstInt::make(0);
	}
      }
      
      //add code to deal with all the other unops
      assert(false);

}

Expression* Evaluator::eval_binop(AstBinOp* b)
{
   Expression* e1 = b->get_first();
  Expression* e2 = b->get_second();
   //cout<<"e1 in binop is: "<<e1->to_value()<<endl;
  //cout<<"e2 in binop is: "<<e2->to_value()<<endl;
 
  Expression* eval_e1 = eval(e1);
  Expression* eval_e2 = eval(e2);
  //cout<<"eval e1 in binop is: "<<eval_e1->to_value()<<endl;
  //cout<<"eval e2 in binop is: "<<eval_e2->to_value()<<endl;
  
  //if not comparing nils
 // if (eval_e1->get_type() != AST_NIL && eval_e2->get_type() != AST_NIL){
    //as long as its not cons?
  //  if (eval_e1->get_type() != eval_e2->get_type() && b->get_binop_type() != CONS)
  //    report_error(b, "Binop can only be applied to expressions of the same type");
  //}
  
  //might have to get value from ast identifiers for some of these binops...
  //I dont think so now...AST IDENTIFIER should take care of all that?
  if(b->get_binop_type() == PLUS) {
    //cout<<"in plus"<<endl;
    //2 integers
    if(eval_e1->get_type() == AST_INT) {
      AstInt* i = static_cast<AstInt*>(eval_e1);
      if(eval_e2->get_type() == AST_INT){
	AstInt* i2 = static_cast<AstInt*>(eval_e2);
	return AstInt::make(i->get_int() + i2->get_int());
      }
      //nil
      else
	return b;
    }
    //two strings
    else if(eval_e1->get_type() == AST_STRING){
      AstString* i = static_cast<AstString*>(eval_e1);
      if(eval_e2->get_type() == AST_STRING){
	AstString* i2 = static_cast<AstString*>(eval_e2);
	return AstString::make(i->get_string() + i2->get_string());
      }
      //nil
      else
	return b;
    }
    else if (eval_e1->get_type() == AST_NIL)
      return b;
    else
      report_error(b, "Binop + can only be applied to strings or integers");
  }
  if(b->get_binop_type() == MINUS){
    if(eval_e1->get_type() == AST_INT) {
      AstInt* i = static_cast<AstInt*>(eval_e1);
      if(eval_e2->get_type() == AST_INT){
	AstInt* i2 = static_cast<AstInt*>(eval_e2);
	return AstInt::make(i->get_int() - i2->get_int());
      }
      //nil
      else
	return b;
    }
    else if (eval_e1->get_type() == AST_NIL)
      return b;
    else
      report_error(b, "Binop - cannot be applied to strings");
  }
  
  if(b->get_binop_type() == TIMES){
    if(eval_e1->get_type() == AST_INT) {
      AstInt* i = static_cast<AstInt*>(eval_e1);
      if(eval_e2->get_type() == AST_INT){
	AstInt* i2 = static_cast<AstInt*>(eval_e2);
	return AstInt::make(i->get_int() * i2->get_int());
      }
      //nil
      else
	return b;
    }
    else if (eval_e1->get_type() == AST_NIL)
      return b;
    else{
     
      report_error(b, "Binop * cannot be applied to strings");
    }
  }
  
  if(b->get_binop_type() == DIVIDE){
    if(eval_e1->get_type() == AST_INT) {
      AstInt* i = static_cast<AstInt*>(eval_e1);
      if(eval_e2->get_type() == AST_INT){
	AstInt* i2 = static_cast<AstInt*>(eval_e2);
	return AstInt::make(i->get_int() / i2->get_int());
      }
      //nil
      else
	return b;
    }
    else if (eval_e1->get_type() == AST_NIL)
      return b;
    else{
       //cout<<"E1 type is "<< eval_e1->get_type()<<endl;
      //cout<<"E2 type is "<< eval_e2->get_type()<<endl;
      report_error(b, "Binop / cannot be applied to strings");
    }
  }
  
  if(b->get_binop_type() == AND){
    if(eval_e1->get_type() == AST_INT) {
      AstInt* i = static_cast<AstInt*>(eval_e1);
      if (i->get_int() == 0)
	 return AstInt::make(0);
      if(eval_e2->get_type() == AST_INT){
	AstInt* i2 = static_cast<AstInt*>(eval_e2);
	if (i2->get_int() == 0)
	  return AstInt::make(0);
	return AstInt::make(1);
      }
      //nil
      else
	return b;
    }
    else if (eval_e1->get_type() == AST_NIL)
      return b;
    else
      report_error(b, "Predicate in conditional must be an integer");
  }
  
  if(b->get_binop_type() == OR){
    if(eval_e1->get_type() == AST_INT) {
      AstInt* i = static_cast<AstInt*>(eval_e1);
      if(eval_e2->get_type() == AST_INT){
	AstInt* i2 = static_cast<AstInt*>(eval_e2);
	if (i->get_int() == 0 && i2->get_int() == 0)
	  return AstInt::make(0);
	return AstInt::make(1);
      }
      //nil
      else
	return b;
    }
    else if (eval_e1->get_type() == AST_NIL)
      return b;
    else
      report_error(b, "Predicate in conditional must be an integer");
  }
  
  if(b->get_binop_type() == EQ){
    //cout<<"in binop eq"<<endl;
    //two integers
    if(eval_e1->get_type() == AST_INT) {
      AstInt* i = static_cast<AstInt*>(eval_e1);
      if(eval_e2->get_type() == AST_INT){
	AstInt* i2 = static_cast<AstInt*>(eval_e2);
	long g = (i->get_int() == i2->get_int());
	return AstInt::make(g);
      }
      //nil
      else
	return b;
    }
    //two strings
    else if(eval_e1->get_type() == AST_STRING) {
      AstString* i = static_cast<AstString*>(eval_e1);
      if(eval_e2->get_type() == AST_STRING){
	AstString* i2 = static_cast<AstString*>(eval_e2);
	long g = (i->get_string() == i2->get_string());
	return AstInt::make(g);
      }
      //nil
      else
	return b;
    }
    else if (eval_e1->get_type() == AST_NIL)
      return b;
    else
       report_error(b, "Binop = can only be applied to integers or strings");
  }
  
  if(b->get_binop_type() == NEQ){
    //two integers
    if(eval_e1->get_type() == AST_INT) {
      AstInt* i = static_cast<AstInt*>(eval_e1);
      if(eval_e2->get_type() == AST_INT){
	AstInt* i2 = static_cast<AstInt*>(eval_e2);
	long g = (i->get_int() != i2->get_int());
	return AstInt::make(g);
      }
      //nil
      else
	return b;
    }
    else if(eval_e1->get_type() == AST_STRING) {
      AstString* i = static_cast<AstString*>(eval_e1);
      if(eval_e2->get_type() == AST_STRING){
	AstString* i2 = static_cast<AstString*>(eval_e2);
	long g = (i->get_string() != i2->get_string());
	return AstInt::make(g);
      }
      //nil
      else
	return b;
    }
    else if (eval_e1->get_type() == AST_NIL)
      return b;
    else
      report_error(b, "Binop <> can only be applied to integers or strings");
  }	
  
  if(b->get_binop_type() == LT){
    if(eval_e1->get_type() == AST_INT) {
      AstInt* i = static_cast<AstInt*>(eval_e1);
      if(eval_e2->get_type() == AST_INT){
	AstInt* i2 = static_cast<AstInt*>(eval_e2);
	long g = (i->get_int() < i2->get_int());
	return AstInt::make(g);
      }
      //nil
      else
	return b;
    }
    else if (eval_e1->get_type() == AST_NIL)
      return b;
    else
      report_error(b, "Binop < can only be applied to integers");
  }
  
  if(b->get_binop_type() == GT){
    if(eval_e1->get_type() == AST_INT) {
      AstInt* i = static_cast<AstInt*>(eval_e1);
      if(eval_e2->get_type() == AST_INT){
	AstInt* i2 = static_cast<AstInt*>(eval_e2);
	long g = (i->get_int() > i2->get_int());
	return AstInt::make(g);
      }
      //nil
      else
	return b;
    }
    else if (eval_e1->get_type() == AST_NIL)
      return b;
    else
      report_error(b, "Binop > can only be applied to integers");
  }
  
  if(b->get_binop_type() == LEQ){
    if(eval_e1->get_type() == AST_INT) {
      AstInt* i = static_cast<AstInt*>(eval_e1);
      if(eval_e2->get_type() == AST_INT){
	AstInt* i2 = static_cast<AstInt*>(eval_e2);
	long g = (i->get_int() <= i2->get_int());
	return AstInt::make(g);
      }
      //nil
      else
	return b;
    }
    else if (eval_e1->get_type() == AST_NIL)
      return b;
    else
      report_error(b, "Binop <= can only be applied to integers");
  }
  
  if(b->get_binop_type() == GEQ){
    if(eval_e1->get_type() == AST_INT) {
      AstInt* i = static_cast<AstInt*>(eval_e1);
      if(eval_e2->get_type() == AST_INT){
	AstInt* i2 = static_cast<AstInt*>(eval_e2);
	long g = (i->get_int() >= i2->get_int());
	return AstInt::make(g);
      }
      //nil
      else
	return b;
    }
    else if (eval_e1->get_type() == AST_NIL)
      return b;
    else
      report_error(b, "Binop >= can only be applied to integers");
  }
  
  if(b->get_binop_type() == CONS){
    Expression* i;
    Expression* i2;
    
    //cout<< "eval e1 is: "<< eval_e1->to_value()<<endl;
    //cout<< "eval e2 is: "<<eval_e2->to_value()<<endl;
    if(eval_e1->get_type() == AST_INT){
      i = static_cast<AstInt*>(eval_e1);
      //first = 0;
    }
    else if(eval_e1->get_type() == AST_STRING){
      i = static_cast<AstString*>(eval_e1);
      //first = 1;
    }
    else if(eval_e1->get_type() == AST_LIST){
      i = static_cast<AstList*>(eval_e1);
    }
    else if(eval_e1->get_type() == AST_NIL){
      i = static_cast<AstNil*>(eval_e1);
    }
    else
      report_error(b, "Invalid type for Binop @");
    if(eval_e2->get_type() == AST_INT){
      i2 = static_cast<AstInt*>(eval_e2);
      //second = 0;
    }
    else if(eval_e2->get_type() == AST_STRING){
      i2 = static_cast<AstString*>(eval_e2);
      //second = 1;
    }
    else if(eval_e2->get_type() == AST_LIST){
      i2 = static_cast<AstList*>(eval_e2);
    }
     else if(eval_e2->get_type() == AST_NIL){
      i2 = static_cast<AstNil*>(eval_e2);
    }
    else
      report_error(b, "Invalid type for Binop @");
    return AstList::make(i, i2);
  }
  
 
    
 
	
  
  
  
  
  assert(false);
}






Expression* Evaluator::eval(Expression* e)
{


	Expression* res_exp = NULL;
	switch(e->get_type())
	{
	
	case AST_UNOP:
	{
		AstUnOp* b = static_cast<AstUnOp*>(e);
		res_exp = eval_unop(b);
		break;
	}
	case AST_BINOP:
	{
		AstBinOp* b = static_cast<AstBinOp*>(e);
		//cout<<"in ASTBINOP: "<<b->to_value()<<endl;
		res_exp = eval_binop(b);
		break;

	  
	}
	case AST_IDENTIFIER:
	{
	  //cout<<"in ast identifier"<<endl;
	  AstIdentifier* b = static_cast<AstIdentifier*>(e);
	  AstString* s = static_cast<AstString*>(e);
	  string p = s->get_string();
	 // AstIdentifierList* l = AstIdentifierList::make(b);
	  //if the id of the identifier is just the name, it means it hasnt been initialized? - NO
	  //cout<<"ast ident is: "<<b->to_value()<<endl;
	  //sym_tab.print_contents();
	  if (sym_tab.find(b) != NULL){
	    //cout<<"in id if"<<endl;
	    //cout<<"value of id is: "<<(sym_tab.find(b))->to_value()<<endl;
	    //sym_tab.print_contents();
	    return sym_tab.find(b);
	  }
	  else{
	    //cout<<"in id else"<<endl;
	    string s1 = "Identifier " + p + " is not bound in current context";
	    //return b;
	    report_error(e, s1);
	  }
	    
	  break;
	}
	case AST_IDENTIFIER_LIST:
	{
	   //Return itself
	  return AstIdentifierList::make();
	 
	}
	case AST_LIST:
	{
	  //cout<<"in ast List"<<endl;
	  AstList* b = static_cast<AstList*>(e);
	  return AstList::make(b->get_hd(), b->get_tl());
	}
	case AST_EXPRESSION_LIST:
	{
	  int lamFlag = 0;
	  AstExpressionList* bodyList;
	  AstExpressionList* newList;
	 //cout<<"in expression list"<<endl;
	 AstExpressionList* b = static_cast<AstExpressionList*>(e);
	 
	 b->make(e);
	 vector<Expression*> vecs = b->get_expressions();
	 
	 //cout<<"vecs size is: "<< vecs.size()<<endl;
	 //b->substitute(3,5);
	 for (int i = vecs.size()-1; i >= 0; i--){
	   //cout<<"in for loop"<<endl;
	   //cout<<"VECS VAL: "<< vecs[i]->to_value() <<endl;
	   //if hte expression is a lambda, replace whats to the right of it according to lambda rules
	   
	   //evaluate identifiers if necessary
	   Expression* evalExpr = eval(vecs[i]);
	   //cout<< "evalExpr value is: "<< evalExpr->to_value()<<endl;
	   //subb in the evaluation for the id;
	   vecs[i] = evalExpr;
	    if (vecs[i]->get_type() == AST_LAMBDA){
	      //cout<<"in if"<<endl;
	      AstLambda* lam = static_cast<AstLambda*>(vecs[i]);
	      //cout<< "TYPE: " << lam->to_value() << endl;
	      Expression* body = lam->get_body();
	      //cout<< "BODY: " << body->to_value() << endl;
	      AstIdentifier* id = lam->get_formal();
	      //cout<< "ID: " << id->to_value() << endl;
	      //if(id->get_type() == AST_IDENTIFIER){
		//cout<<"identifier"<<endl;}
	      //else
		//cout<<"id list"<<endl;
	      if (body->get_type() == AST_LAMBDA){
		//cout <<"Body is lambda"<<endl; 
		bodyList = AstExpressionList::make(body);
		//cout<<"body list before is: "<< bodyList->to_value()<<endl;
		//cout<< "vecs i +2 is "<< vecs[i+2]->to_value()<<endl;
		newList = bodyList;
		int j=i+2;
		//cout<<"j is: "<<j<<endl;
		if (j<vecs.size()){
		  while(j<vecs.size()){
		    newList = newList->append_exp(vecs[j]);
		    j++; 
		  }
		  lamFlag = 1;
		  //cout<<"body list is: "<< newList->to_value()<<endl;
		}
		
		else
		  lamFlag=0;
		
		
	      }
	      //if(i>1){
	      //cout<< "REPLACE exp: " << vecs[i+1]->to_value() << endl;
	      Expression* replaceExp = eval(vecs[i+1]);
	      
	      sym_tab.push();
	      sym_tab.add(id, replaceExp);
	      //}
	      Expression* eval_body;
	      if (lamFlag ==1){
		//cout<<"evaluating newlist: "<< newList->to_value()<<endl;
		eval_body = eval(newList);
	      }
	      else{
		//cout<<"evaluating body: "<< body->to_value()<<endl;
		eval_body = eval(body);
	      }
	      sym_tab.pop();
	      
	      return eval_body;
	    }
	    else{
	      //cout<<"not lambda"<<endl;
	    }
	   
	 }
	 //if vector list starts with lambda or function then we're good
	  string error = "Only lambda expressions can be applied to other expressions";
	  report_error(b, error);
	}
	case AST_LAMBDA:
	{
	  //sym_tab.print_contents();
	  //cout<<"in lambda"<<endl;
	  //cout<< "ID: " << e->to_value() << endl;
	  AstLambda* b = static_cast<AstLambda*>(e);
	  Expression* body = b->get_body();
	  //cout<< "Body: " << body->to_value() << endl;
	  AstIdentifier* id = b->get_formal();
	  //cout<< "ID: " << id->to_value() << endl;
	  //if it's an ast identifier but this till doesnt catch identifiers that are part of other expressions
	  if(body->get_type() == AST_IDENTIFIER){
	    AstIdentifier* bodyID = static_cast<AstIdentifier*>(body);
	    //if the identifier is defined replace it in the lambda
	    if(sym_tab.find(bodyID)){
	      Expression* evalBody = eval(bodyID);
	      //cout<<"eval Body is: "<<evalBody<<endl;
	      return AstLambda::make(id, evalBody);
	    }
	  }
	  return AstLambda::make(id, body);
	}
	case AST_BRANCH:
	{
	   AstBranch* b = static_cast<AstBranch*>(e);
	  
	  //keep recursing until you get types
	  Expression* pred = b->get_pred();
	  Expression* thenExp = b->get_then_exp();
	  Expression* elseExp = b->get_else_exp();
	  Expression* eval_pred = eval(pred);
	  

	  //will resolve to 0 or 1
	  AstInt* eval_pred_int = static_cast<AstInt*>(eval_pred);
	  long eval_pred_INT = eval_pred_int->get_int();
	  if (eval_pred_INT){//True
		  Expression* eval_thenExp = eval(thenExp);
		  return eval_thenExp;
	   }
	    else{//false
		  Expression* eval_elseExp = eval(elseExp);
		  return eval_elseExp;
	    }
	}
	case AST_LET:
	{
	  //cout<<"in ast let"<<endl;
	  AstLet* b = static_cast<AstLet*>(e);
	    AstIdentifier* id = b->get_id();
	    //cout<<"id in let is"<<id->to_value()<<endl;
	    Expression* body = b->get_body();
	    //cout<<"body in let is"<<body->to_value()<<endl;
	    Expression* val = b->get_val();
	    //cout<<"val in let is"<<val->to_value()<<endl;
	    
	    //evaluate what your changing the ID to
	    Expression* eval_val = eval(val);
	    
	    //cout<<"evalval in let is"<<eval_val->to_value()<<endl;
	    
	    sym_tab.push();
	    //cout<<"after pushing"<<endl;
	    //sym_tab.print_contents();
	    //add the value to the sym table
	    sym_tab.add(id, eval_val);
	    //cout<<"after adding"<<endl;
	    //sym_tab.print_contents();
	    //evaluate the body (rest of hte program)
	    Expression* eval_body = eval(body);
	    sym_tab.pop();
	    //cout<<"after popping"<<endl;
	    //sym_tab.print_contents();
	    //return the rest of the program
	    return eval_body;
	  
	} 
	case AST_READ:
	{
		AstRead* r = static_cast<AstRead*>(e);
		string input;
		getline(cin, input);
		if(r->read_integer()) {
			return AstInt::make(string_to_int(input));
		}
		return AstString::make(input);


		break;
	}
	case AST_INT:
	{
		res_exp = e;
		break;
	}
	case AST_STRING:
	{
		AstString* s = static_cast<AstString*>(e);
		return s;
		break;
	}
	case AST_NIL:
	{
// 	  
		return AstNil::make();
		break;

	  
	}
	//ADD CASES FOR ALL EXPRESSIONS!!
	default:
		assert(false);


	}
	return res_exp;
}
