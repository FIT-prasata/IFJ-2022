// Filename: expr.c
// IFJ 2022/2023 project
// TRP variant
//
// Bottom up parser
//
// Author: <xsklen14> - David Sklenář
// Author: <xproch0o> - Marek Procházka
// Author: <xzavad20> - Lukáš Zavadil
// Author: <xsvetl07> - Adam Světlík

// LOCAL INCLUDES
#include "expr.h"

// Precedence table
//
// [ - shift
// ] - reduce
// = - special shift
// ! - error
char ptable[P_TABLE_SIZE][P_TABLE_SIZE] = {
/*
  STACK | INPUT -->
    | 
    v       $    i    +    -    *    /    .   ===  !==   <    >    <=   >=   (    ) */
/*  $  */ {'!', '[', '[', '[', '[', '[', '[', '[', '[', '[', '[', '[', '[', '[', '!'},
/*  i  */ {']', '!', ']', ']', ']', ']', ']', ']', ']', ']', ']', ']', ']', '!', ']'},
/*  +  */ {']', '[', ']', ']', '[', '[', ']', ']', ']', ']', ']', ']', ']', '[', ']'},
/*  -  */ {']', '[', ']', ']', '[', '[', ']', ']', ']', ']', ']', ']', ']', '[', ']'},
/*  *  */ {']', '[', ']', ']', ']', ']', ']', ']', ']', ']', ']', ']', ']', '[', ']'},
/*  /  */ {']', '[', ']', ']', ']', ']', ']', ']', ']', ']', ']', ']', ']', '[', ']'},
/*  .  */ {']', '[', ']', ']', '[', '[', ']', ']', ']', ']', ']', ']', ']', '[', ']'},
/* === */ {']', '[', '[', '[', '[', '[', '[', '!', '!', '!', '!', '!', '!', '[', ']'},
/* !== */ {']', '[', '[', '[', '[', '[', '[', '!', '!', '!', '!', '!', '!', '[', ']'},
/*  <  */ {']', '[', '[', '[', '[', '[', '[', '!', '!', '!', '!', '!', '!', '[', ']'},
/*  >  */ {']', '[', '[', '[', '[', '[', '[', '!', '!', '!', '!', '!', '!', '[', ']'},
/*  <= */ {']', '[', '[', '[', '[', '[', '[', '!', '!', '!', '!', '!', '!', '[', ']'},
/*  >= */ {']', '[', '[', '[', '[', '[', '[', '!', '!', '!', '!', '!', '!', '[', ']'},
/*  (  */ {'!', '[', '[', '[', '[', '[', '[', '[', '[', '[', '[', '[', '[', '[', '='},
/*  )  */ {']', '!', ']', ']', ']', ']', ']', ']', ']', ']', ']', ']', ']', '!', ']'}
};

// Right hand sides of rules
char grammar_rules[RULES_NUM][MAX_RULE_LEN] = {
  {EXPR_NONTERM, EXPR_ADD, EXPR_NONTERM, '\0'},
  {EXPR_NONTERM, EXPR_SUB, EXPR_NONTERM, '\0'},
  {EXPR_NONTERM, EXPR_MUL, EXPR_NONTERM, '\0'},
  {EXPR_NONTERM, EXPR_DIV, EXPR_NONTERM, '\0'},
  {EXPR_NONTERM, EXPR_DOT, EXPR_NONTERM, '\0'},
  {EXPR_ID, '\0'},
  {EXPR_LBR, EXPR_NONTERM, EXPR_RBR, '\0'},
  {EXPR_NONTERM, EXPR_EQ, EXPR_NONTERM, '\0'},
  {EXPR_NONTERM, EXPR_NEQ, EXPR_NONTERM, '\0'},
  {EXPR_NONTERM, EXPR_LT, EXPR_NONTERM, '\0'},
  {EXPR_NONTERM, EXPR_GT, EXPR_NONTERM, '\0'},
  {EXPR_NONTERM, EXPR_LE, EXPR_NONTERM, '\0'},
  {EXPR_NONTERM, EXPR_GE, EXPR_NONTERM, '\0'}
};

ptable_move_t ptable_get_next_move(ptable_symbol_t stack, ptable_symbol_t input) {
  if ((stack < P_TABLE_SIZE && stack >= 0 && input < P_TABLE_SIZE) || input >= 0) {
    switch (ptable[stack][input]) {
      case '[':
        return EXPR_SHIFT;
      case ']':
        return EXPR_REDUCE;
      case '=':
        return EXPR_SPECIAL_SHIFT;
      case '!':
        return EXPR_ERROR;
      default:
        // Incorrect precedence table character
        return EXPR_ERROR;
    }
  }
  else {
    return INTERNAL_ERR;
  }
}

int expr_shift(Char_stack_t *c_stack, char character) {
  char_stack_push_shift(c_stack);
  if (char_stack_push(c_stack, character) == INTERNAL_ERR) {
    return INTERNAL_ERR;
  }
  return OK;
}

int expr_reduce(Char_stack_t *c_stack/*, Token_stack_t *t_stack, Token_t *token*/) {
  DString_t d_string;
  if (d_string_init(&d_string) == INTERNAL_ERR) {
    return INTERNAL_ERR;
  };
  //char head_term = char_stack_get_closest_terminal(c_stack);

  // GENERATE INSTRUCTION HERE

  // Reduction of expression
  char head_char = char_stack_pop(c_stack);
  while (head_char != CHAR_STACK_POP_ERR && head_char != '[') {
    if (d_string_insert_before(&d_string, head_char) == INTERNAL_ERR) {
      d_string_free_and_clear(&d_string);
      return INTERNAL_ERR;
    }
    head_char = char_stack_pop(c_stack);
  }
  if (is_valid_rule(&d_string) == INTERNAL_ERR) {
    d_string_free_and_clear(&d_string);
    return INTERNAL_ERR;
  }
  d_string_free_and_clear(&d_string);

  // Pushing left hand side of rule
  if (char_stack_push(c_stack, 'E') == INTERNAL_ERR) {
    return INTERNAL_ERR;
  }
  return OK;
}

int expr_special_shift(Char_stack_t *c_stack, char character) {
  if (char_stack_push(c_stack, character) == INTERNAL_ERR) {
    return INTERNAL_ERR;
  }
  return OK;
}

int is_valid_rule(DString_t *d_string) {
  for (int i = 0; i < RULES_NUM; i++) {
    if (d_string_cmp(d_string, grammar_rules[i]) == 0) {
      return OK;
    }
  }
  return INTERNAL_ERR;
}

int expr_parse(Char_stack_t *c_stack, Token_stack_t *t_stack, Token_t *token, int location) {
  bool is_logical = false;
  ptable_symbol_t input;

  // Handle logical operators inside assignment
  switch (token->type) {
    case T_EQ:
    case T_NEQ:
    case T_LT:
    case T_GT:
    case T_LEQ:
    case T_GEQ:
      if (location == EXPR_LOC_ASSIGN) {
        return SYNTAX_ERR;
      }
      break;
    default:
      break;
  }
  switch (token->type) {
    case T_ADD:
      input = EXPR_ADD;
      break;
    case T_SUB:
      input = EXPR_SUB;
      break;
    case T_MUL:
      input = EXPR_MUL;
      break;
    case T_DIV:
      input = EXPR_DIV;
      break;
    case T_CONCAT:
      input = EXPR_DOT;
      break;
    case T_LBR:
      input = EXPR_LBR;
      break;
    case T_RBR:
      input = EXPR_RBR;
      break;
    case T_EQ:
      input = EXPR_EQ;
      is_logical = true;
      break;
    case T_NEQ:
      input = EXPR_NEQ;
      is_logical = true;
      break;
    case T_LT:
      input = EXPR_LT;
      is_logical = true;
      break;
    case T_GT:
      input = EXPR_GT;
      is_logical = true;
      break;
    case T_LEQ:
      input = EXPR_LE;
      is_logical = true;
      break;
    case T_GEQ:
      input = EXPR_GE;
      is_logical = true;
      break;
    case T_ID:
      input = EXPR_ID;
      break;
    case T_INT:
    case T_FLOAT:
    case T_STRING:
      input = EXPR_ID;
      token_stack_push(t_stack, token);
      break;
    case T_SEM:
      if (location == EXPR_LOC_ASSIGN || location == EXPR_LOC_RET) {
        return EOEXPR;
      }
      else {
        return SYNTAX_ERR;
      }
    default:
      if (token->type == EOEXPR) {
        input = EXPR_STACK_BOTTOM;
      }
      else {
        return EOEXPR;
      }
      break;
  }
  ptable_symbol_t stack = char_stack_get_closest_terminal(c_stack);
  ptable_move_t next_move = ptable_get_next_move(stack, input);

  switch (next_move) {
    case EXPR_SHIFT:
      return expr_shift(c_stack, input);
    case EXPR_REDUCE:
      return expr_reduce(c_stack/*, t_stack, token*/) == INTERNAL_ERR;
    case EXPR_SPECIAL_SHIFT:
      return expr_special_shift(c_stack, input) == INTERNAL_ERR;
    case EXPR_ERROR:
      return SYNTAX_ERR;
    default:
      return INTERNAL_ERR; // Just how ...
  }
}

int expr_main(Htab_t *table, Token_t *token, int location) {
  Char_stack_t c_stack;
  Token_stack_t t_stack;
  bool load_tokens = true;
  if (char_stack_init(&c_stack) == INTERNAL_ERR) {
    return INTERNAL_ERR;
  }
  if (token_stack_init(&t_stack) == INTERNAL_ERR) {
    return INTERNAL_ERR;
  }
  if (token == NULL) {
    return INTERNAL_ERR;
  }
  if (table == NULL) {
    return INTERNAL_ERR;
  }
  while (load_tokens == true) {
    if (token->type == T_ID) {
      Htab_item_t *item;
      if ((item = htab_find(table, token->attribute.string)) == NULL) {
        return UNDEF_VAR_ERR;
      }
      if (token_stack_push(&t_stack, token) == INTERNAL_ERR) {
        return INTERNAL_ERR;
      }
    }

    int status = expr_parse(&c_stack, &t_stack, token, location);
    if (status == EOEXPR) {
      load_tokens = false;
    }
    else {
      if (status != OK) {
        return status;
      }
      // Get new token
      if ((status = scan(token)) != OK) return status;
    }
    return INTERNAL_ERR; // Generate result instruction here
  }
}