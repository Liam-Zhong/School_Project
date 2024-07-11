#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <string>

bool isInfected(const std::string& virus, const std::string& patientDNA) {
	if (virus.length() > patientDNA.length()) {
		return false; // ���� DNA ���бȻ��� DNA ���г����޷�ƥ��
	}

	std::string doubledPatientDNA = patientDNA + patientDNA;

	if (doubledPatientDNA.find(virus) != std::string::npos) {
		return true; // �ҵ����� DNA ���У���ʾ��Ⱦ
	}

	return false; // δ�ҵ����� DNA ���У�δ��Ⱦ
}

int main() {
	std::string virus, patientDNA;

	while (std::cin >> virus >> patientDNA) {
		if (virus == "0" && patientDNA == "0") {
			break; // �������
		}

		if (isInfected(virus, patientDNA)) {
			std::cout << "YES\n";
		}
		else {
			std::cout << "NO\n";
		}
	}

	return 0;
}
