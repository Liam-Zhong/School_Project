#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// 定义操作符栈的结构
struct OperatorStack {
	char operators[100];
	int top;
};

// 定义操作数栈的结构
struct OperandStack {
	double operands[100];
	int top;
};

// 初始化操作符栈
void initOperatorStack(struct OperatorStack* stack) {
	stack->top = -1;
}

// 初始化操作数栈
void initOperandStack(struct OperandStack* stack) {
	stack->top = -1;
}

// 操作符入栈
void pushOperator(struct OperatorStack* stack, char operator) {
	stack->operators[++stack->top] = operator;
}

// 操作符出栈
char popOperator(struct OperatorStack* stack) {
	return stack->operators[stack->top--];
}

// 操作数入栈
void pushOperand(struct OperandStack* stack, double operand) {
	stack->operands[++stack->top] = operand;
}

// 操作数出栈
double popOperand(struct OperandStack* stack) {
	return stack->operands[stack->top--];
}

// 获取操作符优先级
int getOperatorPriority(char operator) {
	if (operator == '+' || operator == '-') {
		return 1;
	}
	else if (operator == '*' || operator == '/') {
		return 2;
	}
	return 0;
}

// 计算中缀表达式的值
double evaluateInfixExpression(const char* expression) {
	struct OperatorStack operatorStack;
	struct OperandStack operandStack;
	initOperatorStack(&operatorStack);
	initOperandStack(&operandStack);

	int i = 0;
	while (expression[i] != '=') {
		if (expression[i] >= '0' && expression[i] <= '9') {
			// 处理操作数
			double operand = 0.0;
			while (expression[i] >= '0' && expression[i] <= '9') {
				operand = operand * 10 + (expression[i] - '0');
				i++;
			}
			if (expression[i] == '.') {
				i++;
				double decimal = 0.1;
				while (expression[i] >= '0' && expression[i] <= '9') {
					operand += (expression[i] - '0') * decimal;
					decimal *= 0.1;
					i++;
				}
			}
			pushOperand(&operandStack, operand);
		}
		else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
			while (operatorStack.top != -1 && getOperatorPriority(operatorStack.operators[operatorStack.top]) >= getOperatorPriority(expression[i])) {
				char operator = popOperator(&operatorStack);
				double operand2 = popOperand(&operandStack);
				double operand1 = popOperand(&operandStack);
				if (operator == '+') {
					pushOperand(&operandStack, operand1 + operand2);
				}
				else if (operator == '-') {
					pushOperand(&operandStack, operand1 - operand2);
				}
				else if (operator == '*') {
					pushOperand(&operandStack, operand1 * operand2);
				}
				else if (operator == '/') {
					pushOperand(&operandStack, operand1 / operand2);
				}
			}
			pushOperator(&operatorStack, expression[i]);
			i++;
		}
		else if (expression[i] == '(') {

			pushOperator(&operatorStack, expression[i]);
			i++;
		}
		else if (expression[i] == ')') {

			while (operatorStack.top != -1 && operatorStack.operators[operatorStack.top] != '(') {
				char operator = popOperator(&operatorStack);
				double operand2 = popOperand(&operandStack);
				double operand1 = popOperand(&operandStack);
				if (operator == '+') {
					pushOperand(&operandStack, operand1 + operand2);
				}
				else if (operator == '-') {
					pushOperand(&operandStack, operand1 - operand2);
				}
				else if (operator == '*') {
					pushOperand(&operandStack, operand1 * operand2);
				}
				else if (operator == '/') {
					pushOperand(&operandStack, operand1 / operand2);
				}
			}
			popOperator(&operatorStack);  // 弹出左括号
			i++;
		}
		else {
			i++;
		}
	}

	while (operatorStack.top != -1) {
		char operator = popOperator(&operatorStack);
		double operand2 = popOperand(&operandStack);
		double operand1 = popOperand(&operandStack);
		if (operator == '+') {
			pushOperand(&operandStack, operand1 + operand2);
		}
		else if (operator == '-') {
			pushOperand(&operandStack, operand1 - operand2);
		}
		else if (operator == '*') {
			pushOperand(&operandStack, operand1 * operand2);
		}
		else if (operator == '/') {
			pushOperand(&operandStack, operand1 / operand2);
		}
	}

	return operandStack.operands[operandStack.top];
}

int main() {
	char expression[100];
	while (1) {
		scanf("%s", expression);
		if (strcmp(expression, "0") == 0) {
			break;
		}
		double result = evaluateInfixExpression(expression);
		printf("%.2f\n", result);
	}
	return 0;
}