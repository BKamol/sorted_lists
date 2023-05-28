#include <fstream>
#include <iostream>
#include <string>

using namespace std;

struct elem
{
    int info;
    elem* next;
};

elem* create_list(string file_name)
{
    ifstream in(file_name);

    elem* top = new elem;
    elem* p = top;
    in >> top->info;
    while (!in.eof())
    {
        p->next = new elem;
        p = p->next;
        in >> p->info;
    }
    p->next = NULL;

    in.close();
    return top;
}

void show_list(elem* top)
{
    while (top != NULL)
    {
        cout << top->info << ' ';
        top = top->next;
    }
    cout << endl;
}

void add(elem*& top, int x)
{
    bool is_added = false;
    elem* p = top;
    elem* q;
    if (x <= p->info)
    {
        q = new elem;
        q->info = x;
        q->next = p;
        top = q;
        is_added = true;
    }
    else
    {
        while (p->next != NULL && !is_added)
        {
            if (x <= p->next->info)
            {
                q = new elem;
                q->info = x;
                q->next = p->next;
                p->next = q;
                is_added = true;
            }
            else
            {
                p = p->next;
            }
        }
    }
}

elem* merge(elem* top1, elem* top2)
{
    elem* top3 = new elem;
    elem* p3 = top3;
    elem* p1 = top1;
    elem* p2 = top2;

    if (p1->info <= p2->info)
    {
        p3->info = p1->info;
        p1 = p1->next;
    }
    else
    {
        p3->info = p2->info;
        p2 = p2->next;
    }

    while (p1 != NULL && p2 != NULL)
    {
        p3->next = new elem;
        p3 = p3->next;
        if (p1->info <= p2->info)
        {
            p3->info = p1->info;
            p1 = p1->next;
        }
        else
        {
            p3->info = p2->info;
            p2 = p2->next;
        }
    }
    while (p1 != NULL)
    {
        p3->next = new elem;
        p3 = p3->next;
        p3->info = p1->info;
        p1 = p1->next;
    }
    while (p2 != NULL)
    {
        p3->next = new elem;
        p3 = p3->next;
        p3->info = p2->info;
        p2 = p2->next;
    }
    p3->next = NULL;
    return top3;
}

elem* merge_with_destruction(elem* top1, elem* top2)
{
    elem* p1 = top1;
    elem* p12;
    elem* p2 = top2;
    elem* q;
    if (p1->info > p2->info)
    {
        p2 = top1;
        p1 = top2;
    }
    p12 = p1->next;

    while (p12 != NULL && p2 != NULL)
    {
        if (p2->info <= p12->info)
        {
            p1->next = p2;
            q = p2->next;
            p2->next = p12;
            p2 = q;
        }
        p1 = p12;
        p12 = p12->next;
    }

    if (p2 != NULL)
    {
        p1->next = p2;
    }

    if (p1->info > p2->info)
    {
        return top2;
    }
    else
    {
        return top1;
    }
    
}

elem* intersection(elem* top1, elem* top2)
{
    elem* top3 = new elem;
    elem* p1 = top1;
    elem* p2 = top2;
    elem* q = top3;
    while (p1 != NULL && p2 != NULL && p1->info < p2->info)
    {
        p1 = p1->next;
    }
    while (p2 != NULL && p1 != NULL && p2->info < p1->info)
    {
        p2 = p2->next;
    }
    if (p1 != NULL && p2 != NULL && p1->info == p2->info)
    {
        q->info = p1->info;
        p1 = p1->next;
        p2 = p2->next;
    }
    while (p1 != NULL && p2 != NULL)
    {
        if (p1->info == p2->info)
        {
            q->next = new elem;
            q = q->next;
            q->info = p1->info;
            p1 = p1->next;
            p2 = p2->next;
        }
        else if (p1->info < p2->info)
        {
            p1 = p1->next;
        }
        else
        {
            p2 = p2->next;
        }
    }
    q->next = NULL;

    return top3;
}

elem* intersection_with_destruction(elem* top1, elem* top2)
{
    elem* p1;
    elem* p12;
    elem* p2;
    elem* q;
    if (top1->info <= top2->info)
    {
        p1 = top1;
        p2 = top2;
    }
    else
    {
        p1 = top2;
        p2 = top1;
    }
    p12 = p1->next;
    while (p12 != NULL && p2 != NULL)
    {
        if (p12->info == p2->info)
        {
            q = p2;
            p1 = p12;
            p12 = p12->next;
            p2 = p2->next;
            delete q;
        }
        else if (p12->info > p2->info)
        {
            q = p2;
            p2 = p2->next;
            delete q;
        }
        else
        {
            q = p12;
            p1->next = p12->next;
            p12 = p12->next;
            delete q;
        }
    }

    return top1;
}

int main()
{
    elem* top = create_list("nums.txt");
    show_list(top);
    
    //add(top, 1);
    //show_list(top);

    elem* top1 = create_list("nums1.txt");
    show_list(top1);
    elem* top3;

    /*top3 = merge(top, top1);
    show_list(top3);*/

    //top3 = merge_with_destruction(top, top1);
    //show_list(top3);

    top3 = intersection(top, top1);
    show_list(top3);

    //top3 = intersection_with_destruction(top, top1);
    //show_list(top3);
}

