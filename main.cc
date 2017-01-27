#include <bits/stdc++.h>

using namespace std;

int N = 0;
int B = 2;
int s = 0;
int dataset[100000];
int S = 0;
int h = 2;
int ovB = 0;

vector<vector<char> > mem;

int _hash(int K, int m) {
	return (K%(h*m));
}

bool insert_helper(int K, int bucket, int b) {
	char last_char = 'x';
	bool flag = 0;

	do {
		int empty_buckets = int(mem[bucket][0]);
		last_char = mem[bucket][b+1];

		printf("# Empty buckets in %d is %d and last char is %c\n", bucket, empty_buckets, last_char);
		fflush(stdout);

		if (empty_buckets!=0) {
			int index = b - empty_buckets + 1;
			mem[bucket][index] = char(K);
			mem[bucket][0] -= 1;
		}
		else {
			flag = 1;
			if (last_char=='~') {
				vector<char> t;

				t.push_back(char(b-1));
				for (int j=0;j<b;j++) {
					t.push_back(char(-1));
				}	
				t.push_back('~');
				t[1] = char(K);
				mem.push_back(t);

				B+=1;
				ovB+=1;
				mem[bucket][b+1] = char(int(100000/b) + (ovB-1));
			}
			else {
				bucket = int(last_char);
			}
		}
	} while(last_char != '~');

	if (flag==0) {
		return 0;
	}
	return 1;
}

void split_bucket(int b) {
	int index = B - ovB - 1;
	int temp_S = S;
	char last_char = 'x';
	do {
		last_char = mem[temp_S][b+1];
		int empty_buckets = mem[temp_S][0];
		for (int i=1;i<(b-empty_buckets+1);i++) {
			int bucket = _hash(mem[temp_S][i],2);
			if (bucket != temp_S) {
				insert_helper(mem[temp_S][i],bucket,b);
			}
		}
		if (last_char != '~') {
			temp_S = int(last_char);
		}

	} while(last_char != '~');
	

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
		B+=1;
		split_bucket(b);

		int flag = int(((h*2)/2) - 1);
		if (S==flag) {
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
		vector<char> t;
		t.push_back(char(b));
		for (int j=0;j<b;j++) {
			t.push_back(char(-1));
		}
		t.push_back('~');
		mem.push_back(t);
	}
}

int main () {
	int b = 10;
	string db = "db_a.txt";

	initialize_memory(b);
	get_records(db,dataset);

	for(int i=0;i<100000;i++) {
		printf("# Insterting Element %d of value %d from database.\n",i+1, dataset[i]);
		insert(dataset[i], b);
		N += 1;
		// storage_utilization(b);
		// if (N%5000 == 0) {
		// 	int queries[50];
		// 	generate_queries(queries);
		// 	int search_cost = avg_search_cost(queries);
		// }
	}
	for (int i=0;i<b+2;i++) {
		printf("%d",mem[0][i]);
	}
	
	return 0;
}