#include <iostream>
#include <string>
#include <map>

using namespace std;

// ������������ ��� ��� ������� ������
enum class TaskStatus {
  NEW,          // �����
  IN_PROGRESS,  // � ����������
  TESTING,      // �� ������������
  DONE          // ���������
};

// ��������� ���-������� ��� map<TaskStatus, int>,
// ������������ ������� ���������� ����� ������� �������
using TasksInfo = map<TaskStatus, int>;

#include <algorithm>
#include <map>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

// ������� � ��������� ������� ��������� ���������� �� ���������� ���� ������
// ������� �������� ���������� �� ������� ��������: �� �� ������ ���� ����� DONE
// ��� ���� task_status ���� �� ������������ � DONE, ��� ���������
// ������� ��� ������� ����������� �����������
TaskStatus Next(TaskStatus task_status) {
  return static_cast<TaskStatus>(static_cast<int>(task_status) + 1);
}

// ��������� ���-������� ��� map<TaskStatus, int>,
// ������������ ������� ���������� ����� ������� �������
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
  // �������� ���������� �� �������� ����� ����������� ������������
  const TasksInfo& GetPersonTasksInfo(const string& person) const;

  // �������� ����� ������ (� ������� NEW) ��� ����������� ������������
  void AddNewTask(const string& person);

  // �������� ������� �� ������� ���������� ����� ����������� ������������
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
      const string& person, int task_count);

private:
  map<string, TasksInfo> person_tasks_;
};

const TasksInfo& TeamTasks::GetPersonTasksInfo(const string& person) const {
  return person_tasks_.at(person);
}

void TeamTasks::AddNewTask(const string& person) {
  ++person_tasks_[person][TaskStatus::NEW];
}

// ������� ��� �������� ����� �� �������
void RemoveZeros(TasksInfo& tasks_info) {
  // ������ �� �������, ������� ����� ������ �� �������
  vector<TaskStatus> statuses_to_remove;
  for (const auto& task_item : tasks_info) {
    if (task_item.second == 0) {
      statuses_to_remove.push_back(task_item.first);
    }
  }
  for (const TaskStatus status : statuses_to_remove) {
    tasks_info.erase(status);
  }
}


tuple<TasksInfo, TasksInfo> TeamTasks::PerformPersonTasks(
    const string& person, int task_count) {
  TasksInfo updated_tasks, untouched_tasks;

  // ����� � ����� �� ����� ������������ ��� ������, ��� � std::map �������� []
  // � ������ ���������� ����� �������������� �������� �� ���������,
  // ���� ��� ��������.
  // std::map::operator[] ->
  // http://ru.cppreference.com/w/cpp/container/map/operator_at
  TasksInfo& tasks = person_tasks_[person];

  // ���������, ������� ����� ������� �� �������� ����� ��������,
  // ��������� ��� ������, ��� �� ��������� enum class ������������� ��������
  // �� ���� �� �����������.
  // enum class -> http://ru.cppreference.com/w/cpp/language/enum
  for (TaskStatus status = TaskStatus::NEW;
       status != TaskStatus::DONE;
       status = Next(status)) {
    // ������� ����������
    updated_tasks[Next(status)] = min(task_count, tasks[status]);
    // �������, ������� �������� ��������
    task_count -= updated_tasks[Next(status)];
  }

  // ��������� ������ ������� ����� � ������������ � ����������� �� ����������
  // � ������� ���������� ����������
  for (TaskStatus status = TaskStatus::NEW;
       status != TaskStatus::DONE;
       status = Next(status)) {
    untouched_tasks[status] = tasks[status] - updated_tasks[Next(status)];
    tasks[status] += updated_tasks[status] - updated_tasks[Next(status)];
  }
  // �� �������, DONE ������ �� ����� ���������� � �� ���������� �������
  tasks[TaskStatus::DONE] += updated_tasks[TaskStatus::DONE];

  // �� ������� � �������� �� ������ ���� �����
  RemoveZeros(updated_tasks);
  RemoveZeros(untouched_tasks);

  return {updated_tasks, untouched_tasks};
}


// ��������� ������� �� ��������, ����� ����� �����������
// ���������� � ������������� ������ � ������� [] � �������� 0,
// �� ����� ��� ���� �������� �������
void PrintTasksInfo(TasksInfo tasks_info) {
  cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
      ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
      ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
      ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
  TeamTasks tasks;
  tasks.AddNewTask("Ilia");
  for (int i = 0; i < 3; ++i) {
    tasks.AddNewTask("Ivan");
  }
  cout << "Ilia's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
  cout << "Ivan's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

  TasksInfo updated_tasks, untouched_tasks;

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);

  return 0;
}

