#include <iostream>
#include <vector>

bool is_prime(int number)
{
    if(number<2)
    {
        return false;
    }
    if(number==2)
    {
        return true;
    }
    if((number%2)==0)
    {
        return false;
    }
    for(int i=3;i<=number/i;i+=2)
    {
        if(number==i)
        {
            return true;
        }
        if((number%i)==0)
        {
            return false;
        }
    }
    return true;
}

void print_primes()
{
    for(int i=0;i<100;++i)
    {
        if(is_prime(i))
        {
            std::cout<<' '<<i;
        }
    }
    std::cout<<'\n';
}

int calculate_inverse(int number,int modulo)
{
    int result=1;
    while(((number*result)%modulo)!=1)
    {
        ++result;
    }
    return result;
}

void print_inverses()
{
    int p=67;
    for(int i=1;i<p;++i)
    {
        std::cout<<"inv("<<i<<")="<<calculate_inverse(i,p)<<'\n';
    }
}

bool is_valid_point(int x,int y,int p)
{
    int b=7;
    int y_square=static_cast<int>((static_cast<long long>(y)*y)%p);
    int x_square=static_cast<int>((static_cast<long long>(x)*x)%p);
    int x_cube=static_cast<int>((static_cast<long long>(x)*x_square)%p);
    int x_cube_plus_b=static_cast<int>((static_cast<long long>(x_cube)+b)%p);
    return (y_square==x_cube_plus_b);
}

int count_points(int p)
{
    int n=1;
    if(p<=1)
    {
        return n;
    }
    std::vector<int> square_count(p,0);
    for(int y=1;y<p;++y)
    {
        int square=static_cast<int>((static_cast<long long>(y)*y)%p);
        ++square_count[square];
    }
    for(int x=1;x<p;++x)
    {
        int x_square=static_cast<int>((static_cast<long long>(x)*x)%p);
        int x_cube=static_cast<int>((static_cast<long long>(x)*x_square)%p);
        int rhs=static_cast<int>((static_cast<long long>(x_cube)+7)%p);
        n+=square_count[rhs];
    }
    return n;
}

int next_prime(int value)
{
    int result=(value+1);
    while(!(is_prime(result)))
    {
        ++result;
    }
    return result;
}

int previous_prime(int value)
{
    int result=(value-1);
    while(!(is_prime(result)))
    {
        --result;
    }
    return result;
}

void print_counted_points()
{
    int p=67;
    while(p<100)
    {
        std::cout<<"p="<<p<<", n="<<count_points(p)<<'\n';
        p=next_prime(p);
    }
}

struct Point
{
    int x;
    int y;
};

Point find_nearest_point(int p)
{
    Point result{0,0};
    if(p<=1)
    {
        return result;
    }
    std::vector<int> smallest_root(p,0);
    for(int y=1;y<p;++y)
    {
        int square=static_cast<int>((static_cast<long long>(y)*y)%p);
        if(smallest_root[square]==0)
        {
            smallest_root[square]=y;
        }
    }
    for(int x=1;x<p;++x)
    {
        int x_square=static_cast<int>((static_cast<long long>(x)*x)%p);
        int x_cube=static_cast<int>((static_cast<long long>(x)*x_square)%p);
        int rhs=static_cast<int>((static_cast<long long>(x_cube)+7)%p);
        if(smallest_root[rhs]!=0)
        {
            result.x=x;
            result.y=smallest_root[rhs];
            return result;
        }
    }
    return result;
}

void print_first_example()
{
    int p=79;
    Point base=find_nearest_point(p);
    std::cout<<"p="<<p<<", n="<<count_points(p)
             <<", base=("<<base.x<<','<<base.y<<")\n";
}

void find_n_bit(int bits)
{
    int p=previous_prime(1<<bits);
    int min=(1<<(bits-1));
    while(p>min)
    {
        int n=count_points(p);
        if((n!=p)&&(is_prime(n)))
        {
            int second_p=count_points(n);
            if(p==second_p)
            {
                Point base=find_nearest_point(p);
                std::cout<<"p="<<p<<", n="<<count_points(p)
                         <<", base=("<<base.x<<','<<base.y<<") "
                         <<bits<<"-bit\n";
                return;
            }
        }
        p=previous_prime(p);
    }
}

int main()
{
    for(int i=2;i<20;++i)
    {
        find_n_bit(i);
    }
}
