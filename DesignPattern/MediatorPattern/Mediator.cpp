class Mediator;
#include <iostream>
#include <string>
using namespace std;

//������
class Person
{
protected:
	Mediator *m_mediator; //�н�
public:
	virtual void SetMediator(Mediator *mediator) {}  //�����н�
	virtual void SendMessage(string message) {}  //���н鷢����Ϣ
	virtual void GetMessage(string message) {} //���н��ȡ��Ϣ
};

//�����н����
class Mediator
{
public:
	virtual void Send(string message, Person *person) {}
	virtual void SetA(Person *A) {}  //��������һ��
	virtual void SetB(Person *B) {}
};

//�ⷿ��
class Renter : public Person
{
public:
	void SetMediator(Mediator *mediator) { m_mediator = mediator;  }  //�����н�
	void SendMessage(string message) { m_mediator->Send(message, this); }
	void GetMessage(string message) { cout << "�ⷿ���յ���Ϣ��" << message << endl; } //���н��ȡ��Ϣ
};

//����
class Landlord : public Person
{
public:
	void SetMediator(Mediator *mediator) { m_mediator = mediator; }  
	void SendMessage(string message) { m_mediator->Send(message, this); }
	void GetMessage(string message) { cout << "�����յ���Ϣ��" << message << endl; } //���н��ȡ��Ϣ

};

//�����н�
class HouseMediator : public Mediator
{
private:
	Person *m_A; //�ⷿ��
	Person *m_B; //����
public:
	HouseMediator() : m_A(0), m_B(0) {}
	void SetA(Person *A) { m_A = A; }
	void SetB(Person *B) { m_B = B; }
	void Send(string message, Person *person)
	{
		if (person == m_A) //�ⷿ�߸���������Ϣ
			m_B->GetMessage(message); //�����յ���Ϣ
		else
			m_A->GetMessage(message);
	}
};


int main()
{
	Mediator *mediator = new HouseMediator();
	Person *person1 = new Renter(); //�ⷿ��
	Person *person2 = new Landlord(); //����
	mediator->SetA(person1);
	mediator->SetB(person2);
	person1->SetMediator(mediator);
	person2->SetMediator(mediator);
	person1->SendMessage("�����Ҹ�����\n");
	person2->SendMessage("�����и����ӳ���\n");
	delete person1;
	delete person2;
	delete mediator;
	cin.get();
	return 0;
}