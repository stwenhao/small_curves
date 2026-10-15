#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::string to_string_32(std::uint32_t number)
{
    std::ostringstream out;
    out.width(8);
    out.fill('0');
    out<<std::hex<<number;
    return out.str();
}

bool is_prime(std::uint32_t number)
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
    for(std::uint32_t i=3;i<=number/i;i+=2)
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
    for(std::uint32_t i=0;i<100;++i)
    {
        if(is_prime(i))
        {
            std::cout<<' '<<i;
        }
    }
    std::cout<<'\n';
}

std::uint32_t calculate_inverse(std::uint32_t number,std::uint32_t modulo)
{
    std::uint32_t result=1;
    while(((number*result)%modulo)!=1)
    {
        ++result;
    }
    return result;
}

void print_inverses()
{
    std::uint32_t p=67;
    for(std::uint32_t i=1;i<p;++i)
    {
        std::cout<<"inv("<<i<<")="<<calculate_inverse(i,p)<<'\n';
    }
}

bool is_valid_point(std::uint32_t x,std::uint32_t y,std::uint32_t p)
{
    std::uint32_t b=7;
    std::uint32_t y_square=static_cast<std::uint32_t>((static_cast<std::uint64_t>(y)*y)%p);
    std::uint32_t x_square=static_cast<std::uint32_t>((static_cast<std::uint64_t>(x)*x)%p);
    std::uint32_t x_cube=static_cast<std::uint32_t>((static_cast<std::uint64_t>(x)*x_square)%p);
    std::uint32_t x_cube_plus_b=static_cast<std::uint32_t>((static_cast<std::uint64_t>(x_cube)+b)%p);
    return (y_square==x_cube_plus_b);
}

std::uint32_t count_points(std::uint32_t p)
{
    std::uint32_t n=1;
    if(p<=1)
    {
        return n;
    }
    std::vector<std::uint32_t> square_count(p,0);
    for(std::uint32_t y=1;y<p;++y)
    {
        std::uint32_t square=static_cast<std::uint32_t>((static_cast<std::uint64_t>(y)*y)%p);
        ++square_count[square];
    }
    for(std::uint32_t x=1;x<p;++x)
    {
        std::uint32_t x_square=static_cast<std::uint32_t>((static_cast<std::uint64_t>(x)*x)%p);
        std::uint32_t x_cube=static_cast<std::uint32_t>((static_cast<std::uint64_t>(x)*x_square)%p);
        std::uint32_t rhs=static_cast<std::uint32_t>((static_cast<std::uint64_t>(x_cube)+7)%p);
        n+=square_count[rhs];
    }
    return n;
}

std::uint32_t next_prime(std::uint32_t value)
{
    std::uint32_t result=(value+1);
    while(!(is_prime(result)))
    {
        ++result;
    }
    return result;
}

std::uint32_t previous_prime(std::uint32_t value)
{
    std::uint32_t result=(value-1);
    while(!(is_prime(result)))
    {
        --result;
    }
    return result;
}

void print_counted_points()
{
    std::uint32_t p=67;
    while(p<100)
    {
        std::cout<<"p="<<p<<", n="<<count_points(p)<<'\n';
        p=next_prime(p);
    }
}

struct Point
{
    std::uint32_t x;
    std::uint32_t y;
};

Point find_nearest_point(std::uint32_t p)
{
    Point result{0,0};
    if(p<=1)
    {
        return result;
    }
    std::vector<std::uint32_t> smallest_root(p,0);
    for(std::uint32_t y=1;y<p;++y)
    {
        std::uint32_t square=static_cast<std::uint32_t>((static_cast<std::uint64_t>(y)*y)%p);
        if(smallest_root[square]==0)
        {
            smallest_root[square]=y;
        }
    }
    for(std::uint32_t x=1;x<p;++x)
    {
        std::uint32_t x_square=static_cast<std::uint32_t>((static_cast<std::uint64_t>(x)*x)%p);
        std::uint32_t x_cube=static_cast<std::uint32_t>((static_cast<std::uint64_t>(x)*x_square)%p);
        std::uint32_t rhs=static_cast<std::uint32_t>((static_cast<std::uint64_t>(x_cube)+7)%p);
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
    std::uint32_t p=79;
    Point base=find_nearest_point(p);
    std::cout<<"p="<<p<<", n="<<count_points(p)
             <<", base=("<<base.x<<','<<base.y<<")\n";
}

void find_n_bit(std::uint32_t bits)
{
    std::uint32_t p=previous_prime(1<<bits);
    std::uint32_t min=(1<<(bits-1));
    while(p>min)
    {
        std::uint32_t n=count_points(p);
        if((n!=p)&&(is_prime(n)))
        {
            std::uint32_t second_p=count_points(n);
            if(p==second_p)
            {
                Point base=find_nearest_point(p);
                std::cout<<"p=0x"<<to_string_32(p)<<", n="<<to_string_32(count_points(p))
                         <<", base=(0x"<<to_string_32(base.x)<<",0x"<<to_string_32(base.y)<<") "
                         <<bits<<"-bit\n";
                return;
            }
        }
        p=previous_prime(p);
    }
}

int main()
{
    for(std::uint32_t i=2;i<20;++i)
    {
        find_n_bit(i);
    }
}
