#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Task
{
public:
	int time, start, end;

	Task(int s, int e){
		this->start = s;
		this->end = e;
	}
};

class compareTask
{
public:
	bool operator()(const Task left, const Task right) const{
		return left.end > right.end;
	}
};

std::priority_queue<Task, vector<Task>, compareTask> taskQueue;

int calculateTask(int taskNumber){

	int output = 0;

	if (taskNumber > 0) {
		output = 1;
		Task currentTask = taskQueue.top();
		int currentFinal = currentTask.end;
		taskQueue.pop();

		if (taskNumber > 1) {

			for (int i = 1; i < taskNumber; i++){

				currentTask = taskQueue.top();
				
				if (currentTask.start >= currentFinal){
					output++;
					currentFinal = currentTask.end;
				}
				taskQueue.pop();
			}
		}
	}

	return output;
}

int main(int argc, char *argv[]){
	int casos, numTask;

	if (scanf("%i", &casos) != 1)
		cout << "welp" << endl;

	for (int j = 0; j<casos; j++){

		if (scanf("%i ", &numTask) != 1)
			cout << "welp" << endl;

		int s, e;
		Task taskReaded = Task(0,0);
		for (int i = 0; i<numTask; i++){

			if (scanf("%i %i", &s, &e) != 2)
				cout << "welp" << endl;
			else
				taskReaded = Task(s, e);
			taskQueue.push(taskReaded);
		}

		printf("%d\n", calculateTask(numTask));
		taskQueue.empty();
	}
}