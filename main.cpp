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

std::uint32_t multiply_mod(std::uint32_t left,std::uint32_t right,std::uint32_t modulo)
{
    return static_cast<std::uint32_t>((static_cast<std::uint64_t>(left)*right)%modulo);
}

std::uint32_t power_mod(std::uint32_t base,std::uint32_t exponent,std::uint32_t modulo)
{
    std::uint32_t result=1;
    while(exponent>0)
    {
        if((exponent&1U)!=0)
        {
            result=multiply_mod(result,base,modulo);
        }
        base=multiply_mod(base,base,modulo);
        exponent>>=1;
    }
    return result;
}

bool is_prime(std::uint32_t number)
{
    if(number<2)
    {
        return false;
    }
    for(std::uint32_t divisor : {2U,3U,5U,7U,11U})
    {
        if(number==divisor)
        {
            return true;
        }
        if(number%divisor==0)
        {
            return false;
        }
    }

    std::uint32_t odd_part=number-1;
    std::uint32_t powers_of_two=0;
    while((odd_part&1U)==0)
    {
        odd_part>>=1;
        ++powers_of_two;
    }
    for(std::uint32_t witness : {2U,3U,5U,7U,11U})
    {
        if(witness>=number)
        {
            continue;
        }
        std::uint32_t value=power_mod(witness,odd_part,number);
        if(value==1 || value==number-1)
        {
            continue;
        }
        bool probably_prime=false;
        for(std::uint32_t r=1;r<powers_of_two;++r)
        {
            value=multiply_mod(value,value,number);
            if(value==number-1)
            {
                probably_prime=true;
                break;
            }
        }
        if(!probably_prime)
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
    const bool prime=is_prime(p);
    if(prime && p%3==2)
    {
        // Cubing permutes nonzero residues, so only y^2 == 7 is excluded.
        const std::uint32_t seven=7%p;
        const std::uint32_t roots=(power_mod(seven,(p-1)/2,p)==1 ? (p==2 ? 1 : 2) : 0);
        return p-roots;
    }
    if(prime && p%3==1)
    {
        // Nonzero cubes form a subgroup of size (p-1)/3, with three x values per cube.
        std::vector<std::uint64_t> square_bitmap((static_cast<std::uint64_t>(p)+63)/64,0);
        std::uint32_t square=1;
        std::uint32_t square_delta=3%p;
        for(std::uint32_t y=1;y<p;++y)
        {
            square_bitmap[square/64]|=(std::uint64_t(1)<<(square%64));
            if(y+1<p)
            {
                square+=square_delta;
                if(square>=p)
                {
                    square-=p;
                }
                square_delta+=2;
                if(square_delta>=p)
                {
                    square_delta-=p;
                }
            }
        }

        std::vector<std::uint32_t> prime_factors;
        std::uint32_t remaining=p-1;
        for(std::uint32_t divisor=2;divisor<=remaining/divisor;++divisor)
        {
            if(remaining%divisor==0)
            {
                prime_factors.push_back(divisor);
                do
                {
                    remaining/=divisor;
                }
                while(remaining%divisor==0);
            }
        }
        if(remaining>1)
        {
            prime_factors.push_back(remaining);
        }

        std::uint32_t generator=2;
        for(;generator<p;++generator)
        {
            bool is_generator=true;
            for(std::uint32_t factor : prime_factors)
            {
                if(power_mod(generator,(p-1)/factor,p)==1)
                {
                    is_generator=false;
                    break;
                }
            }
            if(is_generator)
            {
                break;
            }
        }
        const std::uint32_t cube_generator=multiply_mod(
            multiply_mod(generator,generator,p),generator,p);
        std::uint32_t cube_residue=1;
        const std::uint32_t seven=7%p;
        for(std::uint32_t i=0;i<(p-1)/3;++i)
        {
            std::uint32_t rhs=cube_residue+seven;
            if(rhs>=p)
            {
                rhs-=p;
            }
            if((square_bitmap[rhs/64]&(std::uint64_t(1)<<(rhs%64)))!=0)
            {
                n+=6;
            }
            cube_residue=multiply_mod(cube_residue,cube_generator,p);
        }
        return n;
    }

    if(!prime)
    {
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

    std::vector<std::uint64_t> square_bitmap((static_cast<std::uint64_t>(p)+63)/64,0);
    std::uint32_t square=1%p;
    std::uint32_t square_delta=3%p;
    const std::uint32_t two=2%p;
    for(std::uint32_t y=1;y<p;++y)
    {
        square_bitmap[square/64]|=(std::uint64_t(1)<<(square%64));
        if(y+1<p)
        {
            square+=square_delta;
            if(square>=p)
            {
                square-=p;
            }
            square_delta+=two;
            if(square_delta>=p)
            {
                square_delta-=p;
            }
        }
    }
    std::uint32_t x_cube=1%p;
    std::uint32_t cube_delta=7%p;
    std::uint32_t cube_second_delta=12%p;
    const std::uint32_t six=6%p;
    const std::uint32_t seven=7%p;
    for(std::uint32_t x=1;x<p;++x)
    {
        std::uint32_t rhs=x_cube+seven;
        if(rhs>=p)
        {
            rhs-=p;
        }
        if((square_bitmap[rhs/64]&(std::uint64_t(1)<<(rhs%64)))!=0)
        {
            n+=(p==2 ? 1 : 2);
        }
        x_cube+=cube_delta;
        if(x_cube>=p)
        {
            x_cube-=p;
        }
        cube_delta+=cube_second_delta;
        if(cube_delta>=p)
        {
            cube_delta-=p;
        }
        cube_second_delta+=six;
        if(cube_second_delta>=p)
        {
            cube_second_delta-=p;
        }
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
    std::uint32_t x_cube=1%p;
    std::uint32_t cube_delta=7%p;
    std::uint32_t cube_second_delta=12%p;
    const std::uint32_t six=6%p;
    const std::uint32_t seven=7%p;
    for(std::uint32_t x=1;x<p;++x)
    {
        std::uint32_t rhs=x_cube+seven;
        if(rhs>=p)
        {
            rhs-=p;
        }
        if(rhs!=0)
        {
            std::uint32_t root=0;
            bool is_square=false;
            if(rhs==1)
            {
                root=1;
                is_square=true;
            }
            else if(power_mod(rhs,(p-1)/2,p)==1)
            {
                if(p%4==3)
                {
                    root=power_mod(rhs,(p+1)/4,p);
                }
                else
                {
                    std::uint32_t odd_part=p-1;
                    std::uint32_t powers_of_two=0;
                    while((odd_part&1U)==0)
                    {
                        odd_part>>=1;
                        ++powers_of_two;
                    }
                    std::uint32_t non_residue=2;
                    while(power_mod(non_residue,(p-1)/2,p)!=p-1)
                    {
                        ++non_residue;
                    }
                    std::uint32_t c=power_mod(non_residue,odd_part,p);
                    std::uint32_t t=power_mod(rhs,odd_part,p);
                    std::uint32_t value=power_mod(rhs,(odd_part+1)/2,p);
                    std::uint32_t m=powers_of_two;
                    while(t!=1)
                    {
                        std::uint32_t i=1;
                        std::uint32_t squared=multiply_mod(t,t,p);
                        while(i<m && squared!=1)
                        {
                            squared=multiply_mod(squared,squared,p);
                            ++i;
                        }
                        std::uint32_t exponent=std::uint32_t(1)<<(m-i-1);
                        std::uint32_t factor=power_mod(c,exponent,p);
                        value=multiply_mod(value,factor,p);
                        std::uint32_t factor_squared=multiply_mod(factor,factor,p);
                        t=multiply_mod(t,factor_squared,p);
                        c=factor_squared;
                        m=i;
                    }
                    root=value;
                }
                is_square=true;
            }
            if(is_square)
            {
                result.x=x;
                result.y=(root<p-root ? root : p-root);
                return result;
            }
        }
        x_cube+=cube_delta;
        if(x_cube>=p)
        {
            x_cube-=p;
        }
        cube_delta+=cube_second_delta;
        if(cube_delta>=p)
        {
            cube_delta-=p;
        }
        cube_second_delta+=six;
        if(cube_second_delta>=p)
        {
            cube_second_delta-=p;
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
                std::cout<<"p=0x"<<to_string_32(p)<<", n=0x"<<to_string_32(n)
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
    for(std::uint32_t i=2;i<25;++i)
    {
        find_n_bit(i);
    }
}
