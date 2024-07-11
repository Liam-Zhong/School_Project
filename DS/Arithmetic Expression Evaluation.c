#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// ���������ջ�Ľṹ
struct OperatorStack {
	char operators[100];
	int top;
};

// ���������ջ�Ľṹ
struct OperandStack {
	double operands[100];
	int top;
};

// ��ʼ��������ջ
void initOperatorStack(struct OperatorStack* stack) {
	stack->top = -1;
}

// ��ʼ��������ջ
void initOperandStack(struct OperandStack* stack) {
	stack->top = -1;
}

// ��������ջ
void pushOperator(struct OperatorStack* stack, char operator) {
	stack->operators[++stack->top] = operator;
}

// ��������ջ
char popOperator(struct OperatorStack* stack) {
	return stack->operators[stack->top--];
}

// ��������ջ
void pushOperand(struct OperandStack* stack, double operand) {
	stack->operands[++stack->top] = operand;
}

// ��������ջ
double popOperand(struct OperandStack* stack) {
	return stack->operands[stack->top--];
}

// ��ȡ���������ȼ�
int getOperatorPriority(char operator) {
	if (operator == '+' || operator == '-') {
		return 1;
	}
	else if (operator == '*' || operator == '/') {
		return 2;
	}
	return 0;
}

// ������׺���ʽ��ֵ
double evaluateInfixExpression(const char* expression) {
	struct OperatorStack operatorStack;
	struct OperandStack operandStack;
	initOperatorStack(&operatorStack);
	initOperandStack(&operandStack);

	int i = 0;
	while (expression[i] != '=') {
		if (expression[i] >= '0' && expression[i] <= '9') {
			// ���������
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
			popOperator(&operatorStack);  // ����������
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