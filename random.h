#ifndef RANDOM_H_
#define RANDOM_H_

class random_gen {
public:
	random_gen(const int &seed=time(0)) {
		srand(seed);
	}
	virtual ~random_gen() = default;

	float prob() {
		return rand() / static_cast<float>(RAND_MAX);
	}

	int prob_int(const int &min_range, const int &max_range) {
		int total_range = max_range - min_range + 1;
		return (rand() % total_range) + min_range;
	}

};

#endif /* RANDOM_H_ */
