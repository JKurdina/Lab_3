#pragma once
#include <iostream>
#include <string>
using namespace std;

enum TypeElement {
	Operation,
	value,
	base
};

class Lexema {
	string str;
	TypeElement type;

public:
	Lexema(string _str = "", TypeElement _type = base) :str(_str), type(_type) {};

	string getStr() { return str; };
	TypeElement getType() { return type; };

	friend ostream& operator<<(ostream& out, Lexema& p) {
		out << "{" << p.str << ", ";
		if (p.type == Operation) {
			out << "operation";
		}
		if (p.type == value) {
			out << "value";
		}
		out << "}";
		return out;
	}
};

template <typename T>
class queue
{
    int size;
    int start;
    int end;
    T* p;

private: int next(int i) { return ((i + 1) % size); }

public:
    queue(int _size = 1)
    {
        size = _size;
        p = new T[size];
        end = 0;
        start = next(end);
    }

    queue(const queue<T>& q)
    {
        size = q.size;
        end = q.end;
        start = q.start;
        p = new T[size];
        for (int i = start; i != next(end); i = next(i))
            p[i] = q.p[i];
    }

    bool empty() { return(next(end) == start); }
    bool IsFull() { return(next(next(end)) == start); }
    queue<T>& operator = (const queue<T>& q)
    {
        if (this == &q)
            return *this;
        if (size > 0)
            delete[]p;
        size = q.size;
        end = q.end;
        start = q.start;
        p = new T[size];
        for (int i = start; i != next(end); i++)
            p[i] = q.p[i];
        return *this;
    }

    int size_q()
    {
        if (empty()) {
            return 0;
        }
        //if (end < start) {
            //return size - start + end + 1;
        //}
        else {
            return end - start + 1;
        }
    }

    void push(T a)
    {
        if (IsFull())
        {

            T* tmp = new T[size*2];
            int ind = 1;
            for (int i = start; i != next(end); i = next(i)) {
                tmp[ind] = p[i];
                ind++;
            }
            delete[]p;
            p = tmp;
            end = size - 1;
            start = 1;
            size = size*2;
        }
        end = next(end);
        p[end] = a;
    }

    T front()
    {
        return p[start];
    }

    T pop()
    {
        if (empty()) throw - 1;
        T v = p[start];
        start = next(start);
        return v;
    }


    friend ostream& operator<<(ostream& out, queue<T>& q)
    {
        if (q.empty())
        {
            out << "queue is empty" << endl;
            return out;
        }
        for (int i = q.start; i != q.next(q.end); i = q.next(i))
            out << q.p[i] << endl;
        //out << endl;
        return out;
    }

    ~queue()
    {
        if (size > 0)
            delete[]p;
    }

};

queue<Lexema> lex(string input) {
    queue<Lexema> res;

    input += " ";

    int i;

    string tmp = "";
    string op = "+-*/()";
    string sep = " \n \t";

    int state = 0;//��������� 

    for (i = 0; i < input.size(); i++) {

        char c = input[i];

        switch (state)
        {

        case 0:// ��������
            if ((c >= '0') && (c <= '9')) {
                tmp = c;
                state = 1;
                break;
            }
            if (op.find(c) >= 0) {//���� ���� � ������ op
                tmp = c;
                Lexema l(tmp, Operation);
                res.push(l);
                state = 0;
                break;
            }
            break;

        case 1://�����
            if ((c >= '0') && (c <= '9')) {
                tmp += c;
                state = 1;
                break;
            }
            if (op.find(c) >= 0) {//���� ���� � ������ op
                Lexema l1(tmp, value);
                res.push(l1);

                tmp = c;
                Lexema l2(tmp, Operation);
                res.push(l2);
                state = 0;
                break;
            }
            if (sep.find(c) >= 0) {

                Lexema l1(tmp, value);
                res.push(l1);
                state = 0;
                break;
            }


            break;

        default:
            break;
        }
    }
    return res;
}

template <typename T>
class stack
{
private:
    T* pMem;
    int size;
    int top;

public:
    stack(int _size = 1)
    {
        if (_size <= 0)
        {
            throw -1;
        }
        top = -1;
        size = _size;
        pMem = new T[size];
    }

    stack(const stack<T>& p)
    {
        if (p.pMem == nullptr)
        {
            pMem = nullptr;
            size = 0;
            top = -1;
        }
        else
        {
            size = p.size;
            top = p.top;
            pMem = new T[size];
            copy(p.pMem, p.pMem + size, pMem);
        }
    }

    int size_s()
    {
        return top + 1;
    }

    bool empty()
    {
        return top == -1;
    }

    bool IsFull()
    {
        return top == size - 1;
    }

    void push(T val)
    {
        if (IsFull())
        {
            T* tmp = new T[size*2];
            copy(pMem, pMem + size, tmp);
            delete[] pMem;
            pMem = tmp;
            size += 1;
        }
        pMem[++top] = val;
    }

    T pop()
    {
        if (empty())
        {
            throw -1;
        }
        T v = pMem[top];
        top--;
        return v;
    }

    T Top()
    {
        if (empty())
        {
            throw -1;
        }
        return pMem[top];
    }

    friend ostream& operator<<(ostream& out, stack<T>& st)
    {
        if (st.IsEmpty())
        {
            out << "stack is empty" << endl;
            return out;
        }
        for (int i = st.top; i >= 0; i--)
            out << st.pMem[i];
        out << endl;
        return out;
    }

    ~stack()
    {
        delete[] pMem;
    }
};

