#include <iostream>

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
    for(int i=3;i*i<=number;i+=2)
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
    int y_square=(y*y)%p;
    int x_square=(x*x)%p;
    int x_cube=(x*x_square)%p;
    int x_cube_plus_b=(x_cube+b)%p;
    return (y_square==x_cube_plus_b);
}

int count_points_slow(int p)
{
    int n=1;
    for(int y=1;y<p;++y)
    {
        for(int x=1;x<p;++x)
        {
            if(is_valid_point(x,y,p))
            {
                ++n;
            }
        }
    }
    //std::cout<<"count_points_slow("<<p<<")="<<n<<'\n';
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

struct Point
{
    int x;
    int y;
};

bool are_points_equal(Point first,Point second)
{
    return (first.x==second.x)&&(first.y==second.y);
}

Point find_nearest_point(int p)
{
    Point result;
    result.x=0;
    result.y=0;
    for(int x=1;x<p;++x)
    {
        for(int y=1;y<p;++y)
        {
            if(is_valid_point(x,y,p))
            {
                result.x=x;
                result.y=y;
                return result;
            }
        }
    }
    return result;
}

Point double_point(Point base,int p)
{
    int px_square=(base.x*base.x)%p;
    int px_square_3=(3*px_square)%p;
    int py_double=(2*base.y)%p;
    int invert_py_double=calculate_inverse(py_double,p);
    int c=(px_square_3*invert_py_double)%p;
    int c_square=(c*c)%p;
    int px_double=(2*base.x)%p;
    int minus_px_double=p-px_double;
    Point result;
    result.x=(c_square+minus_px_double)%p;
    int minus_rx=p-result.x;
    int px_rx_diff=(base.x+minus_rx)%p;
    int c_px_rx_diff=(c*px_rx_diff)%p;
    int minus_py=p-base.y;
    result.y=(c_px_rx_diff+minus_py)%p;
    return result;
}

Point add_points(Point first,Point second,int p)
{
    if(are_points_equal(first,second))
    {
        return double_point(first,p);
    }
    if(first.x==second.x)
    {
        Point zero;
        zero.x=0;
        zero.y=0;
        return zero;
    }
    if((first.x==0)&&(first.y==0))
    {
        return second;
    }
    if((second.x==0)&&(second.y==0))
    {
        return first;
    }
    int minus_py=p-first.y;
    int diff_y=(second.y+minus_py)%p;
    int minus_px=p-first.x;
    int diff_x=(second.x+minus_px)%p;
    int invert_diff_x=calculate_inverse(diff_x,p);
    int c=(diff_y*invert_diff_x)%p;
    int c_square=(c*c)%p;
    int minus_qx=p-second.x;
    Point result;
    result.x=(c_square+minus_px+minus_qx)%p;
    int minus_rx=p-result.x;
    int px_rx_diff=(first.x+minus_rx)%p;
    int c_px_rx_diff=(c*px_rx_diff)%p;
    result.y=(c_px_rx_diff+minus_py)%p;
    return result;
}

int count_points_faster(int p)
{
    int n=1;
    Point base=find_nearest_point(p);
    Point second=double_point(base,p);
    while(!(are_points_equal(second,base)))
    {
        second=add_points(second,base,p);
        ++n;
    }
    //std::cout<<"count_points_faster("<<p<<")="<<n<<'\n';
    return n;
}

void print_first_example()
{
    int p=79;
    Point base=find_nearest_point(p);
    std::cout<<"p="<<p<<", n="<<count_points_faster(p)
             <<", base=("<<base.x<<','<<base.y<<")\n";
}

void find_n_bit(int bits)
{
    int p=previous_prime(1<<bits);
    int min=(1<<(bits-1));
    while(p>min)
    {
        int n=count_points_faster(p);
        if((n!=p)&&(is_prime(n)))
        {
            int second_p=count_points_faster(n);
            if(p==second_p)
            {
                Point base=find_nearest_point(p);
                std::cout<<"p="<<p<<", n="<<n
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
    for(int i=5;i<15;++i)
    {
        find_n_bit(i);
    }
}
