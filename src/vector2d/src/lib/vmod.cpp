#include"lib/vmod.h"
std::vector<std::vector<double>> vmod(const std::vector<const std::vector<double>>& a){
	std::vector<std::vector<double>> b;
	for(auto c:a){
		std::vector<double> e;
		for(auto d:c){
			e.push_back(d*2);
		}
		b.push_back(e);
	}
	return b;

}
