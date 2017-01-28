#include <bits/stdc++.h>

using namespace std;

int N = 0;
int B = 2;
int s = 0;
int dataset[100000];
int S = 0;
int h = 2;

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
	// printf("# Enter\n");
	string last_char = "x";
	bool flag = 0;

	do {
		// printf("HI %d\n", bucket);
		int empty_buckets = stoi(mem[bucket][0]);
		// printf("# Empty Buckets %d\n",empty_buckets);
		last_char = mem[bucket][b+1];

		printf("# Empty buckets in %d is %d and last char is %s\n", bucket, empty_buckets, last_char.c_str());
		fflush(stdout);

		if (empty_buckets!=0) {
			int index = b - empty_buckets + 1;
			mem[bucket][index] = to_string(K);
			int new_empty_count = empty_buckets - 1;
			mem[bucket][0] = to_string(new_empty_count);
			last_char = "~";
			printf("# Data ADDED!\n");
		}
		else {
			flag = 1;
			int new_vector_flag = 0;
			if (last_char=="~") {
				int idx;
				printf("# Creating new bucket\n");
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
					int bucket_index = int((100000/b) + idx);
					printf("%d\n",bucket_index);
					mem[bucket][b+1] = to_string(bucket_index);
					printf("# Created Bucket at %s\n", mem[bucket][b+1].c_str());
				}
				else {
					bitmap[idx] = 1;
					B+=1;
					int bucket_index = int((100000/b) + idx);
					mem[bucket_index][1] = to_string(K);
					printf("%d\n",bucket_index);
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

	printf("%s %s\n",fast.last_char.c_str(), slow.last_char.c_str());

	while(fast.last_char != "~" || (fast.last_char=="~" && fast.arr_idx != b)){
		// printf("# Breakpoint\n");
		// printf("HELLO: %d\n", stoi(mem[10000][0]));
		fflush(stdout);
		if (fast.arr_idx == slow.arr_idx && fast.bucket_idx == slow.bucket_idx) {
			if (mem[fast.bucket_idx][fast.arr_idx] != "-1") {
				// printf("# Breakpoint\n");
				increment_ptr(&fast,b);
				// printf("# Breakpoint\n");
				increment_ptr(&slow,b);
				// printf("# Breakpoint\n");
			}
			else {
				// printf("# Breakpoint\n");
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
	printf("# Finished While Loop\n");

	if (mem[fast.bucket_idx][fast.arr_idx] != "-1") {
		mem[slow.bucket_idx][slow.arr_idx] = mem[fast.bucket_idx][fast.arr_idx];
		mem[fast.bucket_idx][fast.arr_idx] = "-1";

		int bucket_count = stoi(mem[slow.bucket_idx][0]);
		mem[slow.bucket_idx][0] = to_string(bucket_count + 1);
		bucket_count = stoi(mem[fast.bucket_idx][0]);
		mem[fast.bucket_idx][0] = to_string(bucket_count - 1);
	} 

	printf("# Finished If statement\n");
	if (mem[S][b+1] != "~") {
		int bucket_index = stoi(mem[S][b+1]);
		printf("BUCKET INDEX: %d\n", bucket_index);
		string last_char = "x";
		int previous_bucket = S;

		do {
			last_char = mem[bucket_index][b+1];
			printf("LAST CHAR: %s\n",last_char.c_str());
			int empty_buckets = stoi(mem[bucket_index][0]);
			printf("IMP SHIZZ %d\n",empty_buckets);
			if (empty_buckets == b) {
				int idx = int(bucket_index - (100000/b));
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
		last_char = mem[temp_S][b+1];
		empty_buckets = stoi(mem[temp_S][0]);
		for (int i=1;i<(b-empty_buckets+1);i++) {
			int bucket = _hash(stoi(mem[temp_S][i]),2);
			// printf("HASHING BUCKET: %d and VALUE: %d\n",bucket, stoi(mem[temp_S][i]));
			printf("%d\n",i);
			if (bucket != S) {
				printf("# Reshashed\n");
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
		printf("# Updating Buckets\n");
		update_buckets(b);
	}
}	

void insert (int K, int b) {
	int bucket = _hash(K,1);
	printf("# Calculated Hash of value to be %d\n", bucket);

	if (bucket < S) {
		printf("# Calculating higher order Hash\n");
		bucket = _hash(K,2);
		printf("# Hash is %d\n", bucket);
	}
	fflush(stdout);
	bool split = insert_helper(K,bucket,b);

	if (split) {
		printf("# Splitting condition Reached!\n");
		printf("# Bucket to be split is %d\n", S);
		printf("# Hash is %d\n", h);
		for (int i=0;i<mem[S].size();i++) {
			printf("%s ", mem[S][i].c_str());
		}
		printf("\n");
		B+=1;
		split_bucket(b);

		int flag = int(((h*2)/2) - 1);
		if (S==flag) {
			S = 0;
			h = h *2;
		}
		else {
			S+=1;
		}

		// splitting_cost();
	}
}

void lookup (int K) {

}

void get_records (string db, int dataset[]) {
	int count = 100000;

	ifstream File;
    File.open(db);

	for (int i=0;i<count;i++) {
		File >> dataset[i];
	}
}

void initialize_memory(int b) {
	for (int i=0;i<int(100000/b);i++) {
		vector<string> t;
		t.push_back(to_string(b));
		for (int j=0;j<b;j++) {
			t.push_back(to_string(-1));
		}
		t.push_back("~");
		mem.push_back(t);
	}
}

int main () {
	int b = 10;
	string db = "db_a.txt";

	initialize_memory(b);
	get_records(db,dataset);

	for(int i=0;i<100000;i++) {
		printf("%d\n",i+1);
		printf("# Insterting Element %d of value %d from database.\n",i+1, dataset[i]);
		insert(dataset[i], b);
		printf("---------------------------------------\n");
		for (int i=0;i<mem[870].size();i++) {
			printf("%s ",mem[870][i].c_str());
			
		}
		printf("\n---------------------------------------\n");
		N += 1;
		// storage_utilization(b);
		// if (N%5000 == 0) {
		// 	int queries[50];
		// 	generate_queries(queries);
		// 	int search_cost = avg_search_cost(queries);
		// }
	}
	for (int i=0;i<b+2;i++) {
		printf("%s",mem[0][i].c_str());
	}
	
	return 0;
}