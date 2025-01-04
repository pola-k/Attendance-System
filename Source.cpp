#include<iostream>
#include<vector>
#include<string>
#include<ctime>
#include<cmath>
#include<unordered_map>
#include<fstream>
using namespace std;

class Attendance;
class Leave_Management;
class Leave;
class Report;
class Employee;
class Director;
class File_Management;
class User_Account;
class User_Interface;
class Date;
class System;

class Date 
{
private:
	int day;
	int month;
	int year;
	bool isLeapYear(int year)
	{
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	}
	int daysInMonth(int month, int year) 
	{
		switch (month) 
		{
			case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
			case 4: case 6: case 9: case 11: return 30;
			case 2: return isLeapYear(year) ? 29 : 28;
			default: return 0;
		}
	}
	int daysFromStartOfYear()
	{
		int days = day;
		for (int i = 1; i < month; i++) 
		{
			days += daysInMonth(i, year);
		}
		return days;
	}
	int totalDays()
	{
		int days = year * 365 + year / 4 - year / 100 + year / 400;
		return days + daysFromStartOfYear();
	}
public:
	Date()
	{
		day = month = year = 1;
	}
	Date(int d, int m, int y) 
	{
		day = d;
		month = m;
		year = y;
	}
	int differenceInDays(Date& other)
	{
		return abs(this->totalDays() - other.totalDays());
	}
	bool CompareDate(Date& other)
	{
		if (year > other.year)
		{
			return true;
		}
		else if (year == other.year)
		{
			if (month > other.month)
			{
				return true;
			}
			else if (month == other.month)
			{
				if (day > other.day)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	Date GetNextDate() 
	{
		int newDay = day + 1;
		int newMonth = month;
		int newYear = year;

		if (newDay > daysInMonth(month, year))
		{
			newDay = 1;
			newMonth++; 
			if (newMonth > 12) 
			{
				newMonth = 1; 
				newYear++;
			}
		}
		return Date(newDay, newMonth, newYear);
	}
	bool ComesBefore(Date& other) 
	{
		if (year < other.year) return true;
		if (year > other.year) return false;

		if (month < other.month) return true;
		if (month > other.month) return false;

		return day <= other.day;
	}
	int GetDay()
	{
		return day;
	}
	int GetMonth()
	{
		return month;
	}
	int GetYear()
	{
		return year;
	}
	void Print()
	{
		cout << day << "/" << month << "/" << year << endl;
	}
	bool Equal(Date other)
	{
		if (day == other.day && month == other.month && year == other.year)
		{
			return true;
		}
		return false;
	}
	bool IsValid() 
	{
		if (year < 1 || year > 9999) return false;

		if (month < 1 || month > 12) return false;

		if (day < 1 || day > daysInMonth(month, year)) return false;

		return true;
	}
	void SetDay(int d)
	{
		day = d;
	}
	void SetMonth(int m)
	{
		month = m;
	}
	void SetYear(int y)
	{
		year = y;
	}
};

class Attendance
{
private:
	Employee* employee;
	Date date;
	int hours_worked;
public:
	Attendance(Employee*& emp, Date& curr_date, int hours)
	{
		employee = emp;
		date = curr_date;
		hours_worked = hours;
	}
	void SetHoursWorked(int hours)
	{
		hours_worked = hours;
	}
	int GetHoursWorked()
	{
		return hours_worked;
	}
	Date GetDate()
	{
		return date;
	}
	Employee*& GetEmployee()
	{
		return employee;
	}
	void Print()
	{
		cout << "Date: ";
		date.Print();
		cout << "Hours Worked " << hours_worked << endl;
	}
	~Attendance()
	{
		employee = nullptr;
	}
};

class Leave
{
private:
	Employee* employee;
	int id;
	Date start_date;
	Date end_date;
	string reason;
	bool approved_by_supervisor;
	bool requires_director_approval;
	string type;
	char status;
public:
	static int leave_id;
	Leave(Employee*& emp, int leave_id, Date& s_date, Date& e_date, string leave_reason, bool approved , bool requires_approval, string leave_type, char curr_status)
	{
		employee = emp;
		id = leave_id;
		start_date = s_date;
		end_date = e_date;
		reason = leave_reason;
		approved_by_supervisor = approved;
		requires_director_approval = requires_approval;
		type = leave_type;
		status = curr_status;
	}
	int GetID()
	{
		return id;
	}
	Employee*& GetEmployee()
	{
		return employee;
	}
	Date GetStartDate()
	{
		return start_date;
	}
	Date GetEndDate()
	{
		return end_date;
	}
	string GetReason()
	{
		return reason;
	}
	bool GetSupervisorApprovalStatus()
	{
		return approved_by_supervisor;
	}
	void SetSupervisorApprovalStatus(bool status)
	{
		approved_by_supervisor = status;
	}
	bool GetRequiresDirectorApproval()
	{
		return requires_director_approval;
	}
	string GetLeaveType()
	{
		return type;
	}
	virtual string GetLocation()
	{
		return "";
	}
	virtual bool GetApprovedbyDirector()
	{
		return true;
	}
	void Print();
	virtual void SetApprovedbyDirector(bool status)
	{

	}
	void UpdateStatus(char curr_status)
	{
		status = curr_status;
	}
	char GetStatus()
	{
		return status;
	}
	~Leave()
	{
		employee = nullptr;
	}
};

class Casual_Leave : public Leave
{
public:
	Casual_Leave(Employee*& emp, int leave_id, Date& s_date, Date& e_date, string leave_reason, bool approved, bool requires_approval, string leave_type, char status) : Leave(emp, leave_id, s_date, e_date, leave_reason, approved, false, leave_type, status)
	{
	}
	string GetLocation()
	{
		return "-";
	}
	void Print()
	{
		Leave::Print();
	}
};

class Earned_Leave : public Leave
{
private:
	bool approved_by_director;
public:
	Earned_Leave(Employee*& emp, int leave_id, Date& s_date, Date& e_date, string leave_reason, bool approved, bool requires_approval, string leave_type, bool director_approved, char status) : Leave(emp, leave_id, s_date, e_date, leave_reason, approved, true, leave_type, status)
	{
		approved_by_director = director_approved;
	}
	bool GetApprovedbyDirector()
	{
		return approved_by_director;
	}
	void SetApprovedbyDirector(bool status)
	{
		approved_by_director = status;
	}
	string GetLocation()
	{
		return "-";
	}
	void Print()
	{
		Leave::Print();
		cout << "Approved by Director: ";
		if (approved_by_director)
		{
			cout << "Yes" << endl;
		}
		else
		{
			cout << "No" << endl;
		}
	}
};

class Unpaid_Leave : public Leave
{
private:
	bool approved_by_director;
public:
	Unpaid_Leave(Employee*& emp, int leave_id, Date& s_date, Date& e_date, string leave_reason, bool supervisor_approved, bool requires_approval, string leave_type, bool director_approved, char status) : Leave(emp, leave_id, s_date, e_date, leave_reason, supervisor_approved, true, leave_type, status)
	{
		approved_by_director = director_approved;
	}
	bool GetApprovedbyDirector()
	{
		return approved_by_director;
	}
	void SetApprovedbyDirector(bool status)
	{
		approved_by_director = status;
	}
	string GetLocation()
	{
		return "-";
	}
	void Print()
	{
		Leave::Print();
		cout << "Approved by Director: ";
		if (approved_by_director)
		{
			cout << "Yes" << endl;
		}
		else
		{
			cout << "No" << endl;
		}
	}
};

class Official_Leave : public Leave
{
private:
	string location;
public:
	Official_Leave(Employee*& emp, int leave_id, Date& s_date, Date& e_date, string leave_reason, bool approved, bool requires_approval, string leave_type, string loc, char status) : Leave(emp, leave_id, s_date, e_date, leave_reason, approved, false, leave_type, status)
	{
		location = loc;
	}
	string GetLocation()
	{
		return location;
	}
	void Print()
	{
		Leave::Print();
		cout << "Location: " << location << endl;
	}
};

class User_Account
{
private:
	string email;
	string password;
public:
	User_Account(string user_email, string user_password)
	{
		email = user_email;
		password = user_password;
	}
	bool Verify_Credentials(string user_email, string user_password)
	{
		if (user_email == email && user_password == password)
		{
			return true;
		}
		return false;
	}
	string GetEmail()
	{
		return email;
	}
	string GetPassword()
	{
		return password;
	}
};

class Notification
{
private:
	string text;
public:
	Notification(string notification_text)
	{
		text = notification_text;
	}
	string GetText()
	{
		return text;
	}
	~Notification()
	{
	}
};

class Employee
{
private:
	int id;
	string name;
	string department;
	string role;
	Employee* supervisor;
	unordered_map<int,Employee*> employees_under_supervision;
	vector<Attendance*> attendance_records;
	vector<Leave*> leave_records;
	User_Account* account;
	vector<Notification*> notifications;
	int casual_leave_remaining;
	int earned_leave_remaining;
	void DeleteAttendanceRecords()
	{
		for (auto record : attendance_records)
		{
			delete record;
		}

		attendance_records.clear();
	}
	void DeleteLeaveRecords()
	{
		for (auto record : leave_records)
		{
			delete record;
		}

		leave_records.clear();
	}
public:
	Employee(int emp_id, string emp_name, string emp_department, string emp_role, Employee* emp_supervisor, string emp_email, string emp_password)
	{
		id = emp_id;
		name = emp_name;
		department = emp_department;
		role = emp_role;
		supervisor = emp_supervisor;
		account = new User_Account(emp_email, emp_password);
		casual_leave_remaining = 15;
		earned_leave_remaining = 21;
	}
	int GetID()
	{
		return id;
	}
	string GetName()
	{
		return name;
	}
	string GetDepartment()
	{
		return department;
	}
	string GetRole()
	{
		return role;
	}
	Employee*& GetSupervisor()
	{
		return supervisor;
	}
	void SetSupervisor(Employee*& emp_supervisor)
	{
		supervisor = emp_supervisor;
	}
	void Add_Supervised_Employee(Employee*& emp)
	{
		employees_under_supervision[emp->GetID()] = emp;
	}
	void Remove_Supervised_Employee(int id)
	{
		Employee* new_supervisor = nullptr;
		auto remove_emp = employees_under_supervision.find(id);
		employees_under_supervision[id]->SetSupervisor(new_supervisor);
		employees_under_supervision.erase(remove_emp);
		return;
	}
	void Add_Attendance_Record(Attendance*& att)
	{
		attendance_records.push_back(att);
	}
	void Add_Leave_Record(Leave*& leave_record)
	{
		leave_records.push_back(leave_record);
	}
	User_Account*& GetUserAccount()
	{
		return account;
	}
	vector<Attendance*> GetAttendanceRecords()
	{
		return attendance_records;
	}
	void ShowAttendance()
	{
		cout << "Casual Leaves Remaining: " << casual_leave_remaining << endl;
		cout << "Earned Leaves Remaining: " << earned_leave_remaining << endl;
		cout << endl << endl;
		for (int i = 0; i < attendance_records.size(); i++)
		{
			attendance_records[i]->Print();
		}
	}
	unordered_map<int, Employee*> GetUnderSupervisionEmployees()
	{
		return employees_under_supervision;
	}
	vector<Leave*> GetLeaveRecords()
	{
		return leave_records;
	}
	void Set_Casual_Leave_Remaining(int days)
	{
		casual_leave_remaining -= days;
	}
	void Set_Earned_Leave_Remaining(int days)
	{
		earned_leave_remaining -= days;
	}
	int GetCasualLeaveRemaining()
	{
		return casual_leave_remaining;
	}
	int GetEarnedLeaveRemaining()
	{
		return earned_leave_remaining;
	}
	void Add_Notification_Record(Notification*& notification)
	{
		notifications.push_back(notification);
	}
	vector<Notification*> GetNotifications()
	{
		return notifications;
	}
	void DeleteNotifications()
	{
		for (auto notification : notifications)
		{
			delete notification;
		}
		notifications.clear();
	}
	virtual void Approve_Leave(Leave*& leave_record)
	{
		leave_record->SetSupervisorApprovalStatus(true);
	}
	~Employee()
	{
		supervisor = nullptr;
		employees_under_supervision.clear();
		
		if (account != nullptr)
		{
			delete account;
			account = nullptr;
		}

		DeleteNotifications();
		DeleteAttendanceRecords();
		DeleteLeaveRecords();
	}
};

class Director : public Employee
{
public:
	Director(int emp_id, string emp_name, string emp_department, string emp_role, Employee* emp_supervisor, string emp_email, string emp_password) : Employee(emp_id, emp_name, emp_department, emp_role, emp_supervisor, emp_email, emp_password)
	{

	}
	void Approve_Leave(Leave*& leave_record)
	{
		leave_record->SetApprovedbyDirector(true);
		leave_record->SetSupervisorApprovalStatus(true);
	}
	~Director()
	{

	}
};

class File_Management
{
private:
	static File_Management* file_handler;
	File_Management()
	{
		
	}
public:
	unordered_map<int,Employee*> Load_Employee_Data()
	{
		int id;
		string fname;
		string lname;
		string department;
		string role;
		string email;
		string password;
		unordered_map<int,Employee*> employees;
		int casual_leave_remaining;
		int earned_leave_remaining;

		ifstream ReadFile("employee_data.txt");
		while (!ReadFile.eof())
		{
			ReadFile >> id;
			ReadFile >> fname;
			ReadFile >> lname;
			ReadFile >> role;
			ReadFile >> department;
			ReadFile >> email;
			ReadFile >> password;
			for (int i = 0; i < department.size(); i++)
			{
				if (department[i] == '_')
				{
					department[i] = ' ';
				}
			}
			for (int i = 0; i < role.size(); i++)
			{
				if (role[i] == '_')
				{
					role[i] = ' ';
				}
			}

			if (role == "Director")
			{
				Employee* new_emp = new Director(id, fname + " " + lname, department, role, nullptr, email, password);
				employees[id] = new_emp;
			}
			else
			{
				Employee* new_emp = new Employee(id, fname + " " + lname, department, role, nullptr, email, password);
				employees[id] = new_emp;
			}
		}

		ReadFile.close();
		return employees;
	}
	void Load_Supervisor_Data(unordered_map<int,Employee*>& emp, int director_id)
	{
		int emp_id;
		int supervisor_id;

		ifstream ReadFile("supervisor_data.txt");
		while (!ReadFile.eof())
		{
			ReadFile >> emp_id;
			ReadFile >> supervisor_id;
			
			emp[emp_id]->SetSupervisor(emp[supervisor_id]);
			if (supervisor_id != director_id)
			{
				emp[supervisor_id]->Add_Supervised_Employee(emp[emp_id]);
			}
		}

		ReadFile.close();

	}
	void Load_Attendance_Data(unordered_map<int,Employee*>& emp)
	{
		int employee_id;
		int date;
		int month;
		int year;
		int hours_worked;

		ifstream ReadFile("attendance_records.txt");
		while (!ReadFile.eof())
		{
			ReadFile >> employee_id;
			if (employee_id == 0)
			{
				break;
			}
			ReadFile >> date;
			ReadFile >> month;
			ReadFile >> year;
			ReadFile >> hours_worked;
			Date new_date = Date(date, month, year);
			Attendance* attendance_record = new Attendance(emp[employee_id], new_date, hours_worked);
			emp[employee_id]->Add_Attendance_Record(attendance_record);
		}

		ReadFile.close();
	}
	void Save_Employee_Data(unordered_map<int,Employee*>& emp)
	{
		ofstream Write_File("employee_data.txt");
		for (auto employee : emp)
		{
			int id = employee.first;
			string name = employee.second->GetName();
			string role = employee.second->GetRole();
			for (int i = 0; i < role.size(); i++)
			{
				if (role[i] == ' ')
				{
					role[i] = '_';
				}
			}
			string department = employee.second->GetDepartment();
			for (int i = 0; i < department.size(); i++)
			{
				if (department[i] == ' ')
				{
					department[i] = '_';
				}
			}
			string email = employee.second->GetUserAccount()->GetEmail();
			string password = employee.second->GetUserAccount()->GetPassword();

			Write_File << id << " " << name << " " << role << " " << department << " " << email << " " << password << endl;
		}
		Write_File.close();
	}
	void Save_Supervisor_Data(unordered_map<int,Employee*>& emp, int director_id)
	{
		ofstream Write_File("supervisor_data.txt");

		for (auto employee : emp)
		{
			int employee_id = employee.first;
			if (employee_id != director_id)
			{
				int supervisor_id = employee.second->GetSupervisor()->GetID();
				Write_File << employee_id << " " << supervisor_id << endl;
			}
		}

		Write_File.close();
	}
	void Save_Attendance_Data(unordered_map<int,Employee*>& emp)
	{
		ofstream WriteFile("attendance_records.txt");
		vector<Attendance*> attendance_records;

		for (auto employee : emp)
		{
			vector<Attendance*> emp_attendance_records = employee.second->GetAttendanceRecords();
			for (int i = 0; i < emp_attendance_records.size(); i++)
			{
				attendance_records.push_back(emp_attendance_records[i]);
			}
		}

		for (int i = 0; i < attendance_records.size(); i++)
		{
			for (int j = 0; j < attendance_records.size() - 1; j++)
			{
				Date date1 = attendance_records[j]->GetDate();
				Date date2 = attendance_records[j + 1]->GetDate();
				bool swap_records = date1.CompareDate(date2);
				if (swap_records)
				{
					swap(attendance_records[j], attendance_records[j + 1]);
				}
			}
		}

		for (int i = 0; i < attendance_records.size(); i++)
		{
			int employee_id = attendance_records[i]->GetEmployee()->GetID();
			Date date1 = attendance_records[i]->GetDate();
			int day = date1.GetDay();
			int month = date1.GetMonth();
			int year = date1.GetYear();
			int hours_worked = attendance_records[i]->GetHoursWorked();
			
			WriteFile << employee_id << " " << day << " " << month << " " << year << " " << hours_worked << endl;
		}

		WriteFile << "$";
		WriteFile.close();
	}
	void Load_Leaves_Data(unordered_map<int, Employee*>& emp)
	{
		int leave_id;
		int employee_id;
		int s_date;
		int s_month;
		int s_year;
		int e_date;
		int e_month;
		int e_year;
		string reason;
		bool approved_by_supervisor;
		bool requires_director_approval;
		bool approved_by_director;
		string type;
		string location;
		char status;

		ifstream ReadFile("leave_records.txt");
		while (!ReadFile.eof())
		{
			ReadFile >> leave_id;
			if (leave_id == 0)
			{
				break;
			}
			ReadFile >> employee_id;
			ReadFile >> s_date;
			ReadFile >> s_month;
			ReadFile >> s_year;
			ReadFile >> e_date;
			ReadFile >> e_month;
			ReadFile >> e_year;
			ReadFile >> reason;
			ReadFile >> approved_by_supervisor;
			ReadFile >> requires_director_approval;
			ReadFile >> approved_by_director;
			ReadFile >> type;
			ReadFile >> status;
			ReadFile >> location;

			Date start_date = Date(s_date, s_month, s_year);
			Date end_date = Date(e_date, e_month, e_year);
			Leave* leave_record;

			for (int i = 0; i < reason.size(); i++)
			{
				if (reason[i] == '_')
				{
					reason[i] = ' ';
				}
			}

			for (int i = 0; i < location.size(); i++)
			{
				if (location[i] == '_')
				{
					location[i] = ' ';
				}
			}
			
			int difference = start_date.differenceInDays(end_date) + 1;

			if (type == "Casual")
			{
				leave_record = new Casual_Leave(emp[employee_id], leave_id, start_date, end_date, reason, approved_by_supervisor, requires_director_approval, type, status);
				if (status != 'R')
				{
					emp[employee_id]->Set_Casual_Leave_Remaining(difference);
				}
			}
			else if (type == "Earned")
			{
				leave_record = new Earned_Leave(emp[employee_id], leave_id, start_date, end_date, reason, approved_by_supervisor, requires_director_approval, type, approved_by_director, status);
				if (status != 'R')
				{
					emp[employee_id]->Set_Earned_Leave_Remaining(difference);
				}
			}
			else if (type == "Unpaid")
			{
				leave_record = new Unpaid_Leave(emp[employee_id], leave_id, start_date, end_date, reason, approved_by_supervisor, requires_director_approval, type, approved_by_director, status);
			}
			else
			{
				leave_record = new Official_Leave(emp[employee_id], leave_id, start_date, end_date, reason, approved_by_supervisor, requires_director_approval, type, location, status);
			}
			emp[employee_id]->Add_Leave_Record(leave_record);
			Leave::leave_id++;
		}

		ReadFile.close();
	}
	void Save_Leaves_Data(unordered_map<int,Employee*>& emp)
	{
		vector<Leave*> leave_records;

		for (auto employee : emp)
		{
			vector<Leave*> emp_leave_records = employee.second->GetLeaveRecords();
			for (int i = 0; i < emp_leave_records.size(); i++)
			{
				leave_records.push_back(emp_leave_records[i]);
			}
		}

		for (int i = 0; i < leave_records.size(); i++)
		{
			for (int j = 0; j < leave_records.size() - 1; j++)
			{
				int id_1 = leave_records[j]->GetID();
				int id_2 = leave_records[j + 1]->GetID();
				if (id_1 > id_2)
				{
					swap(leave_records[j], leave_records[j + 1]);
				}
			}
		}

		ofstream WriteFile("leave_records.txt");

		for (int i = 0; i < leave_records.size(); i++)
		{
			int leave_id = leave_records[i]->GetID();
			int employee_id = leave_records[i]->GetEmployee()->GetID();
			Date start_date = leave_records[i]->GetStartDate();
			int start_day = start_date.GetDay();
			int start_month = start_date.GetMonth();
			int start_year = start_date.GetYear();
			Date end_date = leave_records[i]->GetEndDate();
			int end_day = end_date.GetDay();
			int end_month = end_date.GetMonth();
			int end_year = end_date.GetYear();
			string reason = leave_records[i]->GetReason();
			bool approved_by_supervisor = leave_records[i]->GetSupervisorApprovalStatus();
			bool requires_approval_by_director = leave_records[i]->GetRequiresDirectorApproval();
			bool approved_by_director = leave_records[i]->GetApprovedbyDirector();
			string type = leave_records[i]->GetLeaveType();
			string location = leave_records[i]->GetLocation();
			char status = leave_records[i]->GetStatus();

			for (int i = 0; i < reason.size(); i++)
			{
				if (reason[i] == ' ')
				{
					reason[i] = '_';
				}
			}

			for (int i = 0; i < location.size(); i++)
			{
				if (location[i] == ' ')
				{
					location[i] = '_';
				}
			}

			WriteFile << leave_id << " " << employee_id << " " << start_day << " " << start_month << " " << start_year << " " << end_day << " " << end_month << " " << end_year << " " << reason << " " << approved_by_supervisor << " " << requires_approval_by_director << " " << approved_by_director << " " << type << " " << status << " " << location << endl;
		}

		WriteFile << "$";
		WriteFile.close();
	}
	void Load_Notification_Data(unordered_map<int, Employee*>& emp)
	{
		int emp_id;
		string text;

		ifstream ReadFile("notifications.txt");
		while (ReadFile >> emp_id >> text)
		{
			for (int i = 0; i < text.size(); i++)
			{
				if (text[i] == '_')
				{
					text[i] = ' ';
				}
			}

			Notification* new_notification = new Notification(text);
			emp[emp_id]->Add_Notification_Record(new_notification);
		}

		ReadFile.close();
	}
	void Save_Notification_Data(unordered_map<int, Employee*>& emp)
	{
		ofstream WriteFile("notifications.txt");
		
		for (auto employee : emp)
		{
			int emp_id = employee.second->GetID();
			vector<Notification*> notifications = employee.second->GetNotifications();
			for (int i = 0; i < notifications.size(); i++)
			{
				string text = notifications[i]->GetText();
				for (int i = 0; i < text.size(); i++)
				{
					if (text[i] == ' ')
					{
						text[i] = '_';
					}
				}
				WriteFile << emp_id << " " << text << endl;
			}
		}

		WriteFile.close();
	}
	static File_Management* GetFileHandler()
	{
		if (file_handler == nullptr)
		{
			file_handler = new File_Management();
		}
		return file_handler;
	}
	static void DeleteFileHandler()
	{
		if (file_handler != nullptr)
		{
			delete file_handler;
			file_handler = nullptr;
		}
	}
	~File_Management()
	{

	}
};

class Leave_Management
{
private:
	vector<Leave*> leave_records;
public:
	Leave_Management()
	{
		leave_records = {};
	}
	void AddLeaveRecords(Leave*& record)
	{
		leave_records.push_back(record);
	}
	void Print()
	{
		cout << endl << endl << "-------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < leave_records.size(); i++)
		{
			leave_records[i]->Print();
			cout << "-------------------------------------------------------------------------------" << endl;
		}
	}
	bool Search(int id)
	{
		for (int i = 0; i < leave_records.size(); i++)
		{
			if (leave_records[i]->GetID() == id)
			{
				return true;
			}
		}
		return false;
	}
	Leave* GetLeaveRecordbyID(int id)
	{
		for (int i = 0; i < leave_records.size(); i++)
		{
			if (leave_records[i]->GetID() == id)
			{
				return leave_records[i];
			}
		}
		return nullptr;
	}
	void RemoveLeaveRecordbyID(int id)
	{
		for (int i = 0; i < leave_records.size(); i++)
		{
			if (leave_records[i]->GetID() == id)
			{
				leave_records.erase(leave_records.begin() + i);
				break;
			}
		}
	}
	bool Empty()
	{
		return leave_records.empty();
	}
	void UpdateLeaveRecord_After_Director_Action(Leave*& leave_record, bool approve)
	{
		Employee* emp = leave_record->GetEmployee();
		Date start_date = leave_record->GetStartDate();
		Date end_date = leave_record->GetEndDate();
		Date stop_date = end_date.GetNextDate();
		int difference = start_date.differenceInDays(end_date) + 1;

		if (approve)
		{
			string notification_text = "Director Approved your Leave Application with ID: " + to_string(leave_record->GetID());
			Notification* new_notification = new Notification(notification_text);
			emp->Add_Notification_Record(new_notification);

			vector<Attendance*> attendance_records = emp->GetAttendanceRecords();

			while (!start_date.Equal(stop_date))
			{
				bool found = false;
				for (int i = 0; i < attendance_records.size(); i++)
				{
					if (start_date.Equal(attendance_records[i]->GetDate()))
					{
						found = true;
						int hours_worked = attendance_records[i]->GetHoursWorked();
						if (hours_worked < 8)
						{
							attendance_records[i]->SetHoursWorked(8);
						}
					}
				}
				if (!found)
				{
					Attendance* new_attendance_record = new Attendance(emp, start_date, 8);
					emp->Add_Attendance_Record(new_attendance_record);
				}
				start_date = start_date.GetNextDate();
			}

			leave_record->UpdateStatus('A');
		}
		else
		{
			string notification_text = "Director Rejected your Leave Application with ID: " + to_string(leave_record->GetID());
			Notification* new_notification = new Notification(notification_text);
			emp->Add_Notification_Record(new_notification);
			leave_record->UpdateStatus('R');
			if (leave_record->GetLeaveType() == "Earned")
			{
				emp->Set_Earned_Leave_Remaining(-difference);
			}
		}
	}
	void UpdateLeaveRecord_After_Supervisor_Action(Leave*& leave_record, bool approve)
	{
		Employee* emp = leave_record->GetEmployee();
		Date start_date = leave_record->GetStartDate();
		Date end_date = leave_record->GetEndDate();
		Date stop_date = end_date.GetNextDate();
		int difference = start_date.differenceInDays(end_date) + 1;

		if (approve)
		{
			string notification_text = "Supervisor Approved your Leave Application with ID: " + to_string(leave_record->GetID());
			Notification* new_notification = new Notification(notification_text);
			emp->Add_Notification_Record(new_notification);

			if (leave_record->GetLeaveType() == "Earned" || leave_record->GetLeaveType() == "Unpaid")
			{
				return;
			}

			vector<Attendance*> emp_attendance_records = emp->GetAttendanceRecords();

			leave_record->UpdateStatus('A');

			while (!start_date.Equal(stop_date))
			{
				bool found = false;
				for (int i = 0; i < emp_attendance_records.size(); i++)
				{
					if (start_date.Equal(emp_attendance_records[i]->GetDate()))
					{
						found = true;
						int hours_worked = emp_attendance_records[i]->GetHoursWorked();
						if (hours_worked < 8)
						{
							emp_attendance_records[i]->SetHoursWorked(8);
						}
					}
				}
				if (!found)
				{
					Attendance* new_attendance_record = new Attendance(emp, start_date, 8);
					emp->Add_Attendance_Record(new_attendance_record);
				}
				start_date = start_date.GetNextDate();
			}
		}
		else
		{
			string notification_text = "Supervisor Rejected your Leave Application with ID: " + to_string(leave_record->GetID());
			Notification* new_notification = new Notification(notification_text);
			emp->Add_Notification_Record(new_notification);
			leave_record->UpdateStatus('R');
			if (leave_record->GetLeaveType() == "Casual")
			{
				emp->Set_Casual_Leave_Remaining(-difference);
			}
			else if (leave_record->GetLeaveType() == "Earned")
			{
				emp->Set_Earned_Leave_Remaining(-difference);
			}
		}
	}
	~Leave_Management()
	{
		leave_records.clear();
	}
};

class Guard
{
public:
	Guard()
	{

	}
	void Mark_Attendance(Employee*& emp)
	{
		cout << "Guard Marking Attendance of " << emp->GetName() << endl;
		time_t t = time(nullptr);
		tm currentTime;
		localtime_s(&currentTime, &t);
		int year = currentTime.tm_year + 1900;
		int month = currentTime.tm_mon + 1;
		int day = currentTime.tm_mday;

		Date new_date = Date(day, month, year);

		cout << "Enter Hours Worked: ";
		bool valid_input = false;
		int hours_worked;
		while (!valid_input)
		{
			try
			{
				cin >> hours_worked;
				if (hours_worked >= 1 && hours_worked <= 15)
				{
					valid_input = true;
				}
				else
				{
					throw runtime_error("");
				}
			}
			catch (runtime_error& e)
			{
				cout << "Invalid Input" << endl;
				cout << "Enter a Valid Input: ";
			}
		}

		Attendance* new_record = new Attendance(emp, new_date, hours_worked);
		emp->Add_Attendance_Record(new_record);
	}
};

class User_Interface
{
private:
	Employee* current_user;
	Leave_Management* leave_manager;
	void SetLeaveManager()
	{
		leave_manager = new Leave_Management();
		unordered_map<int, Employee*> under_supervision_employees = current_user->GetUnderSupervisionEmployees();

		for (auto employee : under_supervision_employees)
		{
			vector<Leave*> leave_records = employee.second->GetLeaveRecords();
			for (int i = 0; i < leave_records.size(); i++)
			{
				if (leave_records[i]->GetStatus() == 'P')
				{
					if (current_user->GetRole() == "Director")
					{
						if (leave_records[i]->GetRequiresDirectorApproval() && !leave_records[i]->GetApprovedbyDirector() && leave_records[i]->GetSupervisorApprovalStatus())
						{
							leave_manager->AddLeaveRecords(leave_records[i]);
						}
						else if (leave_records[i]->GetEmployee()->GetSupervisor()->GetRole() == "Director" && !leave_records[i]->GetSupervisorApprovalStatus())
						{
							leave_manager->AddLeaveRecords(leave_records[i]);
						}
					}
					else
					{
						if (!leave_records[i]->GetSupervisorApprovalStatus())
						{
							leave_manager->AddLeaveRecords(leave_records[i]);
						}
					}
				}
			}
		}
	}
	void TakeAction(bool approve, int id)
	{
		Leave* record = leave_manager->GetLeaveRecordbyID(id);
		leave_manager->RemoveLeaveRecordbyID(id);

		if (record != nullptr)
		{
			if (approve)
			{
				current_user->Approve_Leave(record);
				if (current_user->GetRole() == "Director")
				{
					leave_manager->UpdateLeaveRecord_After_Director_Action(record, 1);
				}
				else
				{
					leave_manager->UpdateLeaveRecord_After_Supervisor_Action(record, 1);
				}
			}
			else
			{
				if (current_user->GetRole() == "Director")
				{
					leave_manager->UpdateLeaveRecord_After_Director_Action(record, 0);
				}
				else
				{
					leave_manager->UpdateLeaveRecord_After_Supervisor_Action(record, 0);
				}
			}
		}
	}
	void PrintNotifications()
	{
		cout << endl;
		cout << "-------------------------------------------------------------------------------" << endl;
		vector<Notification*> notifications = current_user->GetNotifications();
		if (notifications.empty())
		{
			cout << "No New Notifications" << endl;
		}
		else
		{
			for (int i = 0; i < notifications.size(); i++)
			{
				string text = notifications[i]->GetText();
				cout << text << endl;
			}
		}
	}
	void DeleteNotifications()
	{
		current_user->DeleteNotifications();
	}
	void WelcomeUser()
	{
		cout << endl << endl;
		cout << "-------------------------------------------------------------------------------" << endl;
		cout << "Welcome " << current_user->GetName() << endl;
	}
	void ShowAttendance()
	{
		current_user->ShowAttendance();
	}
	void ApplyForLeave()
	{
		cout << "-------------------------------------------------------------------------------" << endl;
		cout << "Press 1 to Apply for Casual Leave" << endl;
		cout << "Press 2 to Apply for Earned Leave" << endl;
		cout << "Press 3 to Apply for Unpaid Leave" << endl;
		cout << "Press 4 to Apply for Official Leave" << endl;

		int user_input;
		bool valid = false;
		int s_date, s_month, s_year, e_date, e_month, e_year;
		Date start_date, end_date;
		string reason, location;

		while (!valid)
		{
			try
			{
				cin >> user_input;
				if (user_input >= 1 && user_input <= 4)
				{
					valid = true;
				}
				else
				{
					throw runtime_error("");
				}
			}
			catch (runtime_error& e)
			{
				cout << "Invalid Input" << endl;
				cout << "Enter a Valid Input: ";
			}
		}

		bool valid_dates = false;
		valid = false;

		while (!valid_dates)
		{
			while (!valid)
			{
				cout << "Give Starting Date Details" << endl;
				cout << "Enter Start Date: ";
				cin >> s_date;
				cout << "Enter Start Month: ";
				cin >> s_month;
				cout << "Enter Start Year: ";
				cin >> s_year;
				start_date.SetDay(s_date);
				start_date.SetMonth(s_month);
				start_date.SetYear(s_year);
				if (start_date.IsValid() && s_year == 2024)
				{
					valid = true;
				}
				else
				{
					cout << "Invalid Date" << endl << "Enter Again" << endl;
				}
			}

			valid = false;

			while (!valid)
			{
				cout << "Give End Date Details" << endl;
				cout << "Enter End Date: ";
				cin >> e_date;
				cout << "Enter End Month: ";
				cin >> e_month;
				cout << "Enter End Year: ";
				cin >> e_year;
				end_date.SetDay(e_date);
				end_date.SetMonth(e_month);
				end_date.SetYear(e_year);
				if (end_date.IsValid() && e_year == 2024)
				{
					valid = true;
				}
				else
				{
					cout << "Invalid Date" << endl << "Enter Again" << endl;
				}
			}

			if (start_date.ComesBefore(end_date))
			{
				valid_dates = true;
			}
		}

		cout << "Enter Reason: ";
		cin.ignore();
		getline(cin, reason);

		if (user_input == 1)
		{
			string type = "Casual";
			int difference = start_date.differenceInDays(end_date) + 1;
			int leaves_remaining = current_user->GetCasualLeaveRemaining();
			if (difference >= 4 || difference > leaves_remaining)
			{
				cout << "You cannot Apply for this Leave" << endl;
			}
			else
			{
				Leave* new_leave_record = new Casual_Leave(current_user, Leave::leave_id, start_date, end_date, reason, false, false, type, 'P');
				Leave::leave_id++;
				current_user->Add_Leave_Record(new_leave_record);
				current_user->Set_Casual_Leave_Remaining(difference);
				cout << "Leave Application Successfully Created" << endl;
			}
		}
		else if (user_input == 2)
		{
			string type = "Earned";
			int difference = start_date.differenceInDays(end_date) + 1;
			int leaves_remaining = current_user->GetEarnedLeaveRemaining();
			if (difference <= 4 || difference > leaves_remaining)
			{
				cout << "You cannot Apply for this Leave" << endl;
			}
			else
			{
				Leave* new_leave_record = new Earned_Leave(current_user, Leave::leave_id, start_date, end_date, reason, false, true, type, false, 'P');
				Leave::leave_id++;
				current_user->Add_Leave_Record(new_leave_record);
				current_user->Set_Earned_Leave_Remaining(difference);
				cout << "Leave Application Successfully Created" << endl;
			}
		}
		else if (user_input == 3)
		{
			string type = "Unpaid";
			Leave* new_leave_record = new Unpaid_Leave(current_user, Leave::leave_id, start_date, end_date, reason, false, true, type, false, 'P');
			Leave::leave_id++;
			current_user->Add_Leave_Record(new_leave_record);
			cout << "Leave Application Successfully Created" << endl;
		}
		else
		{
			string type = "Official";
			cout << "Enter Location: ";
			cin >> location;
			Leave* new_leave_record = new Official_Leave(current_user, Leave::leave_id, start_date, end_date, reason, false, false, type, location, 'P');
			Leave::leave_id++;
			current_user->Add_Leave_Record(new_leave_record);
			cout << "Leave Application Successfully Created" << endl;
		}
	}
public:
	User_Interface()
	{
		current_user = nullptr;
		leave_manager = nullptr;
	}
	void SetCurrentUser(Employee*& emp)
	{
		current_user = emp;
	}
	vector<string> DisplayLoginScreen()
	{
		cout << endl << endl;
		string email;
		string password;
		cout << "Enter an email: ";
		cin >> email;
		cout << "Enter a password: ";
		cin >> password;
		return { email, password };
	}
	void ShowOptions()
	{
		SetLeaveManager();

		WelcomeUser();
		PrintNotifications();
		DeleteNotifications();

		bool logged_in = true;
		while (logged_in)
		{
			cout << "-------------------------------------------------------------------------------" << endl;
			cout << "Press 1 to View Attendance Records" << endl;
			cout << "Press 2 to Apply for Leave" << endl;
			cout << "Press 3 to Approve or Reject Leave Applications" << endl;
			cout << "Press 4 to Logout" << endl;
			int user_input;
			bool valid_input = false;
			while (!valid_input)
			{
				try
				{
					cin >> user_input;
					if (user_input >= 1 && user_input <= 4)
					{
						valid_input = true;
					}
					else
					{
						throw runtime_error("");
					}
				}
				catch (runtime_error& e)
				{
					cout << "Invalid Input" << endl;
					cout << "Enter a Valid Input: ";
				}
			}
			if (user_input == 4)
			{
				logged_in = false;
				Employee* logout = nullptr;
				current_user = logout;
			}
			else if (user_input == 1)
			{
				ShowAttendance();
			}
			else if (user_input == 2)
			{
				if (current_user->GetRole() == "Director")
				{
					cout << "Director Cannot Apply for Leave" << endl;
				}
				else
				{
					ApplyForLeave();
				}
			}
			else
			{
				if (!leave_manager->Empty())
				{
					leave_manager->Print();
					cout << "Enter Leave ID: ";
					int leave_id;
					bool valid_input = false;

					while (!valid_input)
					{
						try
						{
							cin >> leave_id;
							if (leave_manager->Search(leave_id))
							{
								valid_input = true;
							}
							else
							{
								throw runtime_error("");
							}
						}
						catch (runtime_error& e)
						{
							cout << "Invalid Input" << endl;
							cout << "Enter a Valid Input: ";
						}
					}

					cout << "-------------------------------------------------------------------------------" << endl;
					cout << "Enter 1 to Approve Leave" << endl;
					cout << "Enter 2 to Reject Leave" << endl;
					int selection;
					valid_input = false;

					while (!valid_input)
					{
						try
						{
							cin >> selection;
							if (selection == 1 || selection == 2)
							{
								valid_input = true;
							}
							else
							{
								throw runtime_error("");
							}
						}
						catch (runtime_error& e)
						{
							cout << "Invalid Input" << endl;
							cout << "Enter a Valid Input: ";
						}
					}
					if (selection == 1)
					{
						TakeAction(true, leave_id);
					}
					else
					{
						TakeAction(false, leave_id);
					}
				}
				else
				{
					cout << "Currently There is No Leave Application to Approve" << endl;
				}
			}
		}
	}
	~User_Interface()
	{
		current_user = nullptr;

		if (leave_manager != nullptr)
		{
			delete leave_manager;
			leave_manager = nullptr;
		}
	}
};

class Report
{
public:
	virtual void Generate_Report(System& system)
	{

	}
};

class Attendance_Report : public Report
{
public:
	void Generate_Report(System& system);
};

class Employee_Attendance_Detail : public Report
{
public:
	void Generate_Report(System& system);
};

class Outstanding_Leave_Report : public Report
{
public:
	void Generate_Report(System& system);
};

class Employee_Leave_Detail : public Report
{
public:
	void Generate_Report(System& system);
};

class System
{
private:
	unordered_map<int, Employee*> employees;
	Employee* Director;
	Guard* guard;
	static System* Attendance_System;
	System()
	{
		guard = new Guard();
		Director = nullptr;
	}
public:
	static System* GetAttendanceSystem()
	{
		if (Attendance_System == nullptr)
		{
			Attendance_System = new System();
		}
		return Attendance_System;
	}
	void LoadDataFromFile()
	{
		File_Management* file_reader = File_Management::GetFileHandler();
		employees = file_reader->Load_Employee_Data();

		int director_id = 0;
		for (auto emp : employees)
		{
			if (emp.second->GetRole() == "Director")
			{
				Director = emp.second;
				director_id = emp.first;
				for (auto employee : employees)
				{
					if (employee.second->GetID() != director_id)
					{
						employees[director_id]->Add_Supervised_Employee(employee.second);
					}
				}
				break;
			}
		}

		file_reader->Load_Supervisor_Data(employees, director_id);
		file_reader->Load_Attendance_Data(employees);
		file_reader->Load_Leaves_Data(employees);
		file_reader->Load_Notification_Data(employees);
	}
	void SaveDataToFile()
	{
		File_Management* file_writer = File_Management::GetFileHandler();
		file_writer->Save_Employee_Data(employees);
		file_writer->Save_Supervisor_Data(employees, Director->GetID());
		file_writer->Save_Attendance_Data(employees);
		file_writer->Save_Leaves_Data(employees);
		file_writer->Save_Notification_Data(employees);
	}
	unordered_map<int, Employee*>& GetEmployees()
	{
		return employees;
	}
	void Display_Start_Screen()
	{
		bool close_system = false;
		while (!close_system)
		{
			cout << "-----------------------------------------------------------------------------" << endl;
			cout << "Press 1 to Generate Reports" << endl;
			cout << "Press 2 to Login" << endl;
			cout << "Press 3 to Close the System" << endl;
			cout << "-----------------------------------------------------------------------------" << endl;
			int user_input;
			bool valid_input = false;
			while (!valid_input)
			{
				try
				{
					cin >> user_input;
					if (user_input >= 1 && user_input <= 3)
					{
						valid_input = true;
					}
					else
					{
						throw runtime_error("");
					}
				}
				catch (runtime_error& e)
				{
					cout << "Invalid Input" << endl;
					cout << "Enter a Valid Input: ";
				}
			}
			if (user_input == 3)
			{
				close_system = true;
			}
			else if (user_input == 2)
			{
				User_Interface user_interface;
				bool logged_in = false;
				while (!logged_in)
				{
					vector<string> credentials = user_interface.DisplayLoginScreen();
					string email = credentials[0];
					string password = credentials[1];

					for (auto employee : employees)
					{
						string user_email = employee.second->GetUserAccount()->GetEmail();
						string user_password = employee.second->GetUserAccount()->GetPassword();
						if (email == user_email && user_password == password)
						{
							logged_in = true;
							user_interface.SetCurrentUser(employee.second);
							guard->Mark_Attendance(employee.second);
							break;
						}
					}

					if (!logged_in)
					{
						cout << "Invalid Credentials" << endl;
						cout << "Enter Valid Credentials" << endl;
						cout << endl << endl;
					}
				}
				user_interface.ShowOptions();
			}
			else if (user_input == 1)
			{
				cout << "-----------------------------------------------------------------------------" << endl;
				cout << "Press 1 to Generate Attendance Report of Employees" << endl;
				cout << "Press 2 to Generate Outstanding Leaves Report" << endl;
				cout << "Press 3 to Generate Attendance Report of a Specific Employee" << endl;
				cout << "Press 4 to Generate Leave Report of a Specific Employee" << endl;
				cout << "-----------------------------------------------------------------------------" << endl;
				int report_input;
				bool valid = false;
				while (!valid)
				{
					try
					{
						cin >> report_input;
						if (report_input >= 1 && report_input <= 4)
						{
							valid = true;
						}
						else
						{
							throw runtime_error("");
						}
					}
					catch (runtime_error& e)
					{
						cout << "Invalid Input" << endl;
						cout << "Enter a Valid Input: ";
					}
				}
				if (report_input == 1)
				{
					Report* report = new Attendance_Report();
					report->Generate_Report(*this);
				}
				else if (report_input == 2)
				{
					Report* report = new Outstanding_Leave_Report();
					report->Generate_Report(*this);
				}
				else if (report_input == 3)
				{
					Report* report = new Employee_Attendance_Detail();
					report->Generate_Report(*this);
				}
				else
				{
					Report* report = new Employee_Leave_Detail();
					report->Generate_Report(*this);
				}
				cout << "Report Successfully Created" << endl;
			}
		}
		SaveDataToFile();
	}
	void RunSystem()
	{
		LoadDataFromFile();
		Display_Start_Screen();
	}
	static void DestroyAttendanceSystem() 
	{
		if (Attendance_System != nullptr)
		{
			delete Attendance_System;
			Attendance_System = nullptr;
		}
	}
	~System()
	{
		Director = nullptr;

		if (guard != nullptr)
		{
			delete guard;
			guard = nullptr;
		}

		for (auto employee : employees)
		{
			delete employee.second;
		}

		employees.clear();
	}
};

void Attendance_Report::Generate_Report(System& system)
{
	int percentage;
	int month_number;
	int year;
	time_t t = time(nullptr);
	tm currentTime;
	localtime_s(&currentTime, &t);
	int curr_year = currentTime.tm_year + 1900;

	cout << "Enter Percentage: ";
	bool valid_input = false;

	while (!valid_input)
	{
		try
		{
			cin >> percentage;
			if (percentage >= 1 && percentage <= 100)
			{
				valid_input = true;
			}
			else
			{
				throw runtime_error("");
			}
		}
		catch (runtime_error& e)
		{
			cout << "Invalid Input" << endl;
			cout << "Enter a Valid Input: ";
		}
	}

	valid_input = false;

	cout << "Enter Month Number: ";
	while (!valid_input)
	{
		try
		{
			cin >> month_number;
			if (month_number >= 1 && month_number <= 12)
			{
				valid_input = true;
			}
			else
			{
				throw runtime_error("");
			}
		}
		catch (runtime_error& e)
		{
			cout << "Invalid Input" << endl;
			cout << "Enter a Valid Input: ";
		}
	}

	valid_input = false;
	cout << "Enter Year Number: ";
	while (!valid_input)
	{
		try
		{
			cin >> year;
			if (year >= 2024 && year <= curr_year)
			{
				valid_input = true;
			}
			else
			{
				throw runtime_error("");
			}
		}
		catch (runtime_error& e)
		{
			cout << "Invalid Input" << endl;
			cout << "Enter a Valid Input: ";
		}
	}


	int working_days;
	int total_working_hours;

	if (month_number == 1 || month_number == 3 || month_number == 5 || month_number == 7 || month_number == 8 || month_number == 10 || month_number == 12)
	{
		working_days = 23;
	}
	else if (month_number == 4 || month_number == 6 || month_number == 9 || month_number == 11)
	{
		working_days = 22;
	}
	else
	{
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		{
			working_days = 21;
		}
		else
		{
			working_days = 20;
		}
	}

	total_working_hours = working_days * 8;
	float hours_required = total_working_hours * (percentage / 100.0);
	string filename = "Attendance Report of Month " + to_string(month_number) + " Year " + to_string(year);
	string file = filename + ".txt";

	ofstream WriteFile(file);

	WriteFile << "\t\t" << filename << endl << endl;

	unordered_map<int, Employee*> employees = system.GetEmployees();
	for (auto emp : employees)
	{
		float hours_worked = 0;
		vector<Attendance*> attendance_records = emp.second->GetAttendanceRecords();
		for (int i = 0; i < attendance_records.size(); i++)
		{
			int record_month = attendance_records[i]->GetDate().GetMonth();
			int record_year = attendance_records[i]->GetDate().GetYear();
			if (record_month == month_number && record_year == year)
			{
				hours_worked += attendance_records[i]->GetHoursWorked();
			}
		}
		if (hours_worked < hours_required)
		{
			int emp_id = emp.second->GetID();
			string emp_name = emp.second->GetName();
			WriteFile << "ID: " << emp_id << "\tName: " << emp_name << "\tHours Worked: " << hours_worked << "\tHours Required: " << hours_required << endl;
		}
	}

	WriteFile.close();
}
void Employee_Attendance_Detail::Generate_Report(System& system)
{
	unordered_map<int, Employee*> employees = system.GetEmployees();

	cout << "Choose Employee ID from the Following: " << endl;

	for (auto emp : employees)
	{
		cout << emp.first << endl;
	}

	int emp_id;
	bool valid_input = false;

	cout << "Enter Employee ID: ";

	while (!valid_input)
	{
		try
		{
			cin >> emp_id;
			if (employees.find(emp_id) != employees.end())
			{
				valid_input = true;
			}
			else
			{
				throw runtime_error("");
			}
		}
		catch (runtime_error& e)
		{
			cout << "Invalid Input" << endl;
			cout << "Enter a Valid Input: ";
		}
	}

	vector<Attendance*> attendance_records = employees[emp_id]->GetAttendanceRecords();
	string filename = employees[emp_id]->GetName() + " Attendance Report";
	string file = filename + ".txt";

	ofstream WriteFile(file);
	WriteFile << "\t\t" << filename << endl;

	for (int i = 0; i < attendance_records.size(); i++)
	{
		int day = attendance_records[i]->GetDate().GetDay();
		int month = attendance_records[i]->GetDate().GetMonth();
		int year = attendance_records[i]->GetDate().GetYear();
		int hours_worked = attendance_records[i]->GetHoursWorked();
		WriteFile << "Date: " << day << "/" << month << "/" << year << "\tHours Worked: " << hours_worked << endl;
	}

	WriteFile.close();
}
void Outstanding_Leave_Report::Generate_Report(System& system)
{
	unordered_map<int, Employee*> employees = system.GetEmployees();
	ofstream WriteFile("Outstanding Leave Report.txt");

	WriteFile << "\t\t Outstanding Leave Report" << endl;

	for (auto emp : employees)
	{
		vector<Leave*> leave_records = emp.second->GetLeaveRecords();
		for (int i = 0; i < leave_records.size(); i++)
		{
			if (!leave_records[i]->GetSupervisorApprovalStatus())
			{
				WriteFile << "-----------------------------------------------------------------------------" << endl;
				WriteFile << "Leave ID: " << leave_records[i]->GetID() << endl;
				WriteFile << "Applied by Employee ID: " << leave_records[i]->GetEmployee()->GetID() << endl;
				WriteFile << "Not Approved by Supervisor" << endl;
				WriteFile << "-----------------------------------------------------------------------------" << endl;
			}
			else if (leave_records[i]->GetSupervisorApprovalStatus() && leave_records[i]->GetRequiresDirectorApproval() && !leave_records[i]->GetApprovedbyDirector())
			{
				WriteFile << "-----------------------------------------------------------------------------" << endl;
				WriteFile << "Leave ID: " << leave_records[i]->GetID() << endl;
				WriteFile << "Applied by Employee ID: " << leave_records[i]->GetEmployee()->GetID() << endl;
				WriteFile << "Approved by Supervisor" << endl;
				WriteFile << "Not Approved by Director" << endl;
				WriteFile << "-----------------------------------------------------------------------------" << endl;
			}
		}
	}

	WriteFile.close();

}
void Employee_Leave_Detail::Generate_Report(System& system)
{
	unordered_map<int, Employee*> employees = system.GetEmployees();

	cout << "Choose Employee ID from the Following: " << endl;

	for (auto emp : employees)
	{
		cout << emp.first << endl;
	}

	cout << "Enter Employee ID: ";

	int emp_id;
	bool valid_input = false;

	while (!valid_input)
	{
		try
		{
			cin >> emp_id;
			if (employees.find(emp_id) != employees.end())
			{
				valid_input = true;
			}
			else
			{
				throw runtime_error("");
			}
		}
		catch (runtime_error& e)
		{
			cout << "Invalid Input" << endl;
			cout << "Enter a Valid Input: ";
		}
	}

	vector<Leave*> leave_records = employees[emp_id]->GetLeaveRecords();
	string filename = employees[emp_id]->GetName() + " Leave Report";
	string file = filename + ".txt";

	ofstream WriteFile(file);
	WriteFile << "\t\t" << filename << endl;

	int casual_leave_remaining = employees[emp_id]->GetCasualLeaveRemaining();
	int earned_leave_remaining = employees[emp_id]->GetEarnedLeaveRemaining();

	for (int i = 0; i < leave_records.size(); i++)
	{
		int leave_id = leave_records[i]->GetID();
		Date start_date = leave_records[i]->GetStartDate();
		int start_day = start_date.GetDay();
		int start_month = start_date.GetMonth();
		int start_year = start_date.GetYear();
		Date end_date = leave_records[i]->GetEndDate();
		int end_day = end_date.GetDay();
		int end_month = end_date.GetMonth();
		int end_year = end_date.GetYear();
		string reason = leave_records[i]->GetReason();
		bool approved_by_supervisor = leave_records[i]->GetSupervisorApprovalStatus();
		bool requires_approval_by_director = leave_records[i]->GetRequiresDirectorApproval();
		string type = leave_records[i]->GetLeaveType();
		string location = leave_records[i]->GetLocation();
		char status = leave_records[i]->GetStatus();
		bool approved_by_director = leave_records[i]->GetApprovedbyDirector();

		WriteFile << "-----------------------------------------------------------------------------" << endl;
		WriteFile << "Leave ID: " << leave_id << endl;
		WriteFile << "Start Date: " << start_day << "/" << start_month << "/" << start_year << endl;
		WriteFile << "End Date: " << end_day << "/" << end_month << "/" << end_year << endl;
		WriteFile << "Reason: " << reason << endl;

		if (status == 'P')
		{
			WriteFile << "Status: Pending" << endl;
		}
		else if (status == 'A')
		{
			WriteFile << "Status: Approved" << endl;
		}
		else if (status == 'R')
		{
			WriteFile << "Status: Rejected" << endl;
		}

		WriteFile << "Approved By Supervisor: ";
		if (approved_by_supervisor)
		{
			WriteFile << "Yes" << endl;
		}
		else
		{
			WriteFile << "No" << endl;
		}
		WriteFile << "Requires Director Approval: ";
		if (requires_approval_by_director)
		{
			WriteFile << "Yes" << endl;
			WriteFile << "Approved By Director: ";
			if (approved_by_director)
			{
				WriteFile << "Yes" << endl;
			}
			else
			{
				WriteFile << "No" << endl;
			}
			
		}
		else
		{
			WriteFile << "No" << endl;
		}
		WriteFile << "Leave Type: " << type << endl;
		if(location != "-")
		{
			WriteFile << "Location: " << location << endl;
		}
		WriteFile << "-----------------------------------------------------------------------------" << endl;
	}

	WriteFile << "Casual Leaves Remaining: " << casual_leave_remaining << endl;
	WriteFile << "Earned Leaves Remaining: " << earned_leave_remaining << endl;

	WriteFile.close();
}
void Leave::Print()
{
	cout << "Leave ID: " << id << endl;
	cout << "Applied by Employee with ID: " << employee->GetID() << endl;
	cout << "Start Date: ";
	start_date.Print();
	cout << "End Date: ";
	end_date.Print();
	cout << "Reason: " << reason << endl;
	cout << "Status: ";
	if (status == 'P')
	{
		cout << "Pending" << endl;
	}
	else if (status == 'A')
	{
		cout << "Approved" << endl;
	}
	else if (status == 'R')
	{
		cout << "Rejected" << endl;
	}
	cout << "Approved By Supervisor: ";
	if (approved_by_supervisor)
	{
		cout << "Yes" << endl;
	}
	else
	{
		cout << "No" << endl;
	}
	cout << "Requires Director Approval: ";
	if (requires_director_approval)
	{
		cout << "Yes" << endl;
	}
	else
	{
		cout << "No" << endl;
	}
	cout << "Leave Type: " << type << endl;
}
int Leave::leave_id = 2001;
System* System::Attendance_System = nullptr;
File_Management* File_Management::file_handler = nullptr;

int main()
{
	System* Attendance_System = System::GetAttendanceSystem();
	Attendance_System->RunSystem();
	File_Management::DeleteFileHandler();
	System::DestroyAttendanceSystem();
}