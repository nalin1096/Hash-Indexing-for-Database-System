#include <bits/stdc++.h>

using namespace std;

int N = 0;
int B = 2;
int s = 0;
int dataset[100000];
int S = 0;
int h = 2;

int MAX_BUCKETS = pow(2.0,14.0);
int TOTAL_RECORDS = 100000;
int S_COST = 0;
double SEARCH = 0.0;

vector<double> storage_util;
vector<int> split_cost;
vector<int> records_count;
vector<double> search_cost;

struct ptrs {
	int arr_idx;
	int bucket_idx;
	string last_char;
};

vector<int> bitmap;
vector<vector<string> > mem;

int _hash(int K, int m) {
	return (K%(h*m));
}

bool insert_helper(int K, int bucket, int b) {
	string last_char = "x";
	bool flag = 0;

	do {
		int empty_buckets = stoi(mem[bucket][0]);
		last_char = mem[bucket][b+1];

		if (empty_buckets!=0) {
			int index = b - empty_buckets + 1;
			mem[bucket][index] = to_string(K);
			int new_empty_count = empty_buckets - 1;
			mem[bucket][0] = to_string(new_empty_count);
			last_char = "~";
		}
		else {
			flag = 1;
			int new_vector_flag = 0;
			if (last_char=="~") {
				int idx;
				if (bitmap.empty()) {
					new_vector_flag = 1;
					idx = 0;
					bitmap.push_back(1);
				}
				else {
					int bit_flag = 0;
					for (int i=0;i<bitmap.size();i++) {
						if (bitmap[i]==0) {
							bit_flag = 1;
							idx = i;
							break;
						}
					}
					if (bit_flag == 0) {
						new_vector_flag = 1;
						idx = bitmap.size();
						bitmap.push_back(1);
					}
				}
				if (new_vector_flag) {
					vector<string> t;

					t.push_back(to_string(b-1));
					for (int j=0;j<b;j++) {
						t.push_back(to_string(-1));
					}	
					t.push_back("~");
					t[1] = to_string(K);
					mem.push_back(t);

					B+=1;
					int bucket_index = int((MAX_BUCKETS) + idx);
					mem[bucket][b+1] = to_string(bucket_index);
				}
				else {
					bitmap[idx] = 1;
					B+=1;
					int bucket_index = int((MAX_BUCKETS) + idx);
					mem[bucket_index][1] = to_string(K);
					mem[bucket][b+1] = to_string(bucket_index);
				}
			}
			else {
				bucket = stoi(last_char);
			}
		}
	} while(last_char != "~");

	if (flag==0) {
		return 0;
	}
	return 1;
}

void increment_ptr(struct ptrs* ptr, int b) {
	if (ptr->arr_idx < b) {
		ptr->arr_idx+=1;
	}
	else {
		ptr->arr_idx=1;
		ptr->bucket_idx = stoi(ptr->last_char);
		ptr->last_char = mem[ptr->bucket_idx][b+1];
	}
}

void update_buckets(int b) {
	struct ptrs fast,slow;
	int bucket = S;

	fast.arr_idx = slow.arr_idx = 1;
	fast.bucket_idx = slow.bucket_idx = S;
	fast.last_char = slow.last_char = mem[S][b+1];

	while(fast.last_char != "~" || (fast.last_char=="~" && fast.arr_idx != b)){
		fflush(stdout);
		if (fast.arr_idx == slow.arr_idx && fast.bucket_idx == slow.bucket_idx) {
			if (mem[fast.bucket_idx][fast.arr_idx] != "-1") {
				increment_ptr(&fast,b);
				increment_ptr(&slow,b);
			}
			else {
				increment_ptr(&fast,b);
			}
			fflush(stdout);
		}
		else {
			if (mem[fast.bucket_idx][fast.arr_idx] != "-1") {
				mem[slow.bucket_idx][slow.arr_idx] = mem[fast.bucket_idx][fast.arr_idx];
				mem[fast.bucket_idx][fast.arr_idx] = "-1";

				int bucket_count = stoi(mem[slow.bucket_idx][0]);
				mem[slow.bucket_idx][0] = to_string(bucket_count - 1);
				bucket_count = stoi(mem[fast.bucket_idx][0]);
				mem[fast.bucket_idx][0] = to_string(bucket_count + 1);

				increment_ptr(&fast,b);
				increment_ptr(&slow,b);
			} 
			else {
				increment_ptr(&fast,b);
			}
		}
	}

	if (mem[fast.bucket_idx][fast.arr_idx] != "-1") {
		mem[slow.bucket_idx][slow.arr_idx] = mem[fast.bucket_idx][fast.arr_idx];
		mem[fast.bucket_idx][fast.arr_idx] = "-1";

		int bucket_count = stoi(mem[slow.bucket_idx][0]);
		mem[slow.bucket_idx][0] = to_string(bucket_count - 1);
		bucket_count = stoi(mem[fast.bucket_idx][0]);
		mem[fast.bucket_idx][0] = to_string(bucket_count + 1);
	} 

	if (mem[S][b+1] != "~") {
		int bucket_index = stoi(mem[S][b+1]);
		string last_char = "x";
		int previous_bucket = S;

		do {
			last_char = mem[bucket_index][b+1];
			int empty_buckets = stoi(mem[bucket_index][0]);
			if (empty_buckets == b) {
				int idx = int(bucket_index - (MAX_BUCKETS));
				bitmap[idx] = 0;
				B -=1;
				mem[bucket_index][b+1] = "~";
				mem[previous_bucket][b+1] = "~";
			}
			if (last_char != "~") {
				previous_bucket = bucket_index;
				bucket_index = stoi(last_char);
			}

		} while(last_char != "~");
	}

}

void split_bucket(int b) {
	int index = B - accumulate(bitmap.begin(), bitmap.end(), 0) - 1;
	int temp_S = S;
	int flag = 0;
	int empty_buckets;
	string last_char = "x";

	do {
		S_COST++;
		last_char = mem[temp_S][b+1];
		empty_buckets = stoi(mem[temp_S][0]);
		for (int i=1;i<(b-empty_buckets+1);i++) {
			int bucket = _hash(stoi(mem[temp_S][i]),2);
			if (bucket != S) {
				S_COST++;
				flag = 1;
				insert_helper(stoi(mem[temp_S][i]),bucket,b);
				mem[temp_S][i] = to_string(-1);

				int temp = stoi(mem[temp_S][0]);
				mem[temp_S][0] = to_string(temp+1);
			}
		}
		if (last_char != "~") {
			temp_S = stoi(last_char);
		}

	} while(last_char != "~");

	if (flag == 1) {
		update_buckets(b);
	}
}	

void splitting_cost() {
	split_cost.push_back(S_COST);
	records_count.push_back(N);
	S_COST = 0;
}

void insert (int K, int b) {
	int bucket = _hash(K,1);

	if (bucket < S) {
		bucket = _hash(K,2);
	}
	bool split = insert_helper(K,bucket,b);

	if (split) {
		B+=1;
		split_bucket(b);
		splitting_cost();


		int flag = int(((h*2)/2) - 1);
		if (S==flag) {
			S = 0;
			h = h *2;
		}
		else {
			S+=1;
		}
	}
}

void get_records (string db, int dataset[]) {
	int count = TOTAL_RECORDS;

	ifstream File;
    File.open(db);

	for (int i=0;i<count;i++) {
		File >> dataset[i];
	}
}

void initialize_memory(int b) {
	for (int i=0;i<int(MAX_BUCKETS);i++) {
		vector<string> t;
		t.push_back(to_string(b));
		for (int j=0;j<b;j++) {
			t.push_back(to_string(-1));
		}
		t.push_back("~");
		mem.push_back(t);
	}
}

void storage_utilization (int b) {
	double calc = (double)N/(B*b);
	storage_util.push_back(calc);
}

void generate_queries (int queries[]) {
	int random_numbers[50];
	for (int i=0;i<50;i++) {
		int randNum = rand()%(100000 + 1);
		random_numbers[i] = randNum;
	}

	for (int i=0;i<50;i++) {
		queries[i] = dataset[random_numbers[i]];
	}
}

int lookup (int K, int b) {
	int bucket = _hash(K,1);

	if (bucket < S) {
		bucket = _hash(K,2);
	}

	int count = 0;
	int empty_buckets;
	string last_char = "x";

	do {
		count++;
		last_char = mem[bucket][b+1];
		empty_buckets = stoi(mem[bucket][0]);
		for (int i=1;i<(b-empty_buckets+1);i++) {
			if (stoi(mem[bucket][i]) == K){
				SEARCH += count;
				return 1;
			}
		}

		if (last_char != "~") {
			bucket = stoi(last_char);
		}
	} while (last_char != "~");
	return 0;

}

void avg_search_cost (int queries[], int b) {
	int s_count = 0;
	int success = 0;
	for (int i=0;i<50;i++) {
		success = lookup(queries[i], b);
		s_count += success;
	}
	double cost = (double)SEARCH/s_count;
	search_cost.push_back(cost);
	SEARCH = 0;
}

void makefiles(string db) {
	ofstream File;
    File.open("su_"+db+".txt");

	for (int i=0;i<storage_util.size();i++) {
		File << storage_util[i] << endl;
	}
	File.close();

    File.open("sc_"+db+".txt");

	for (int i=0;i<split_cost.size();i++) {
		File << split_cost[i] << endl;
	}
	File.close();

	File.open("records_"+db+".txt");

	for (int i=0;i<records_count.size();i++) {
		File << records_count[i] << endl;
	}
	File.close();

	File.open("searchc_"+db+".txt");

	for (int i=0;i<search_cost.size();i++) {
		File << search_cost[i] << endl;
	}
	File.close();
}

void initilize() {
	N = 0;
	B = 2;
	s = 0;
	S = 0;
	h = 2;
	S_COST = 0;
	SEARCH = 0.0;

	storage_util.clear();
	split_cost.clear();
	records_count.clear();
	search_cost.clear();
	mem.clear();
	bitmap.clear();
}

void run (int buc_cap, int max_buckets, string db) {
	initilize();
	int b = buc_cap;
	MAX_BUCKETS = max_buckets;

	initialize_memory(b);
	get_records(db,dataset);
	printf("%d\n",MAX_BUCKETS);

	for(int i=0;i<TOTAL_RECORDS;i++) {
		insert(dataset[i], b);
		N += 1;
		storage_utilization(b);
		if (N%5000 == 0) {
			int queries[50];
			generate_queries(queries);
			avg_search_cost(queries,b);
		}
	}
	makefiles(db);
}

int main () {
	run(10,pow(2.0,14.0),"db_a");
	run(70,pow(2.0,12.0),"db_b");

	return 0;
}