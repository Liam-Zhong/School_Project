#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <string>

bool isInfected(const std::string& virus, const std::string& patientDNA) {
	if (virus.length() > patientDNA.length()) {
		return false; // 病毒 DNA 序列比患者 DNA 序列长，无法匹配
	}

	std::string doubledPatientDNA = patientDNA + patientDNA;

	if (doubledPatientDNA.find(virus) != std::string::npos) {
		return true; // 找到病毒 DNA 序列，表示感染
	}

	return false; // 未找到病毒 DNA 序列，未感染
}

int main() {
	std::string virus, patientDNA;

	while (std::cin >> virus >> patientDNA) {
		if (virus == "0" && patientDNA == "0") {
			break; // 输入结束
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
