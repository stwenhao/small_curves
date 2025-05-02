#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

std::string toString8(std::uint8_t value)
{
    std::ostringstream out;
    out.width(2);
    out.fill('0');
    out<<std::hex<<((static_cast<std::uint32_t>(value))&0xff);
    return out.str();
}

std::string toString32(std::uint32_t value)
{
    std::ostringstream out;
    out.width(8);
    out.fill('0');
    out<<std::hex<<value;
    return out.str();
}

std::string toStringRoundNumber(std::size_t i)
{
    std::ostringstream out;
    out.width(2);
    out<<i;
    return out.str();
}

std::string toStringRound(std::size_t i,std::uint32_t a,std::uint32_t b,std::uint32_t c,std::uint32_t d,std::uint32_t e,std::uint32_t f,std::uint32_t g,std::uint32_t h)
{
    std::string str=toStringRoundNumber(i)+" | ";
    str+=toString32(a);
    str+=" ";
    str+=toString32(b);
    str+=" ";
    str+=toString32(c);
    str+=" ";
    str+=toString32(d);
    str+=" ";
    str+=toString32(e);
    str+=" ";
    str+=toString32(f);
    str+=" ";
    str+=toString32(g);
    str+=" ";
    str+=toString32(h);
    return str;
}

std::uint32_t shr3(std::uint32_t value)
{
    return value>>3;
}

std::uint32_t shr10(std::uint32_t value)
{
    return value>>10;
}

std::uint32_t ror6(std::uint32_t value)
{
    return (value<<26)|(value>>6);
}

std::uint32_t ror2(std::uint32_t value)
{
    return (value<<30)|(value>>2);
}

std::uint32_t ror7(std::uint32_t value)
{
    return (value<<25)|(value>>7);
}

std::uint32_t ror11(std::uint32_t value)
{
    return (value<<21)|(value>>11);
}

std::uint32_t ror13(std::uint32_t value)
{
    return (value<<19)|(value>>13);
}

std::uint32_t ror17(std::uint32_t value)
{
    return (value<<15)|(value>>17);
}

std::uint32_t ror18(std::uint32_t value)
{
    return (value<<14)|(value>>18);
}

std::uint32_t ror19(std::uint32_t value)
{
    return (value<<13)|(value>>19);
}

std::uint32_t ror22(std::uint32_t value)
{
    return (value<<10)|(value>>22);
}

std::uint32_t ror25(std::uint32_t value)
{
    return (value<<7)|(value>>25);
}

std::uint32_t s0(std::uint32_t value)
{
    return ror7(value)^ror18(value)^shr3(value);
}

std::uint32_t s1(std::uint32_t value)
{
    return ror17(value)^ror19(value)^shr10(value);
}

std::uint32_t s2(std::uint32_t value)
{
    return ror6(value)^ror11(value)^ror25(value);
}

std::uint32_t s3(std::uint32_t value)
{
    return ror2(value)^ror13(value)^ror22(value);
}

std::uint32_t ch(std::uint32_t e,std::uint32_t f,std::uint32_t g)
{
    return (e&f)^((~e)&g);
}

std::uint32_t maj(std::uint32_t a,std::uint32_t b,std::uint32_t c)
{
    return (a&b)^(a&c)^(b&c);
}

int main()
{
    std::uint32_t a00=0x6a09e667;
    std::uint32_t b00=0xbb67ae85;
    std::uint32_t c00=0x3c6ef372;
    std::uint32_t d00=0xa54ff53a;
    std::uint32_t e00=0x510e527f;
    std::uint32_t f00=0x9b05688c;
    std::uint32_t g00=0x1f83d9ab;
    std::uint32_t h00=0x5be0cd19;
    const std::uint32_t k00=0x428a2f98;
    const std::uint32_t k01=0x71374491;
    const std::uint32_t k02=0xb5c0fbcf;
    const std::uint32_t k03=0xe9b5dba5;
    std::uint32_t w00=0x80000000;
    std::uint32_t w01=0x00000000;
    std::uint32_t w02=0x00000000;
    std::uint32_t w03=0x00000000;
    std::uint32_t z00=h00+s2(e00)+ch(e00,f00,g00)+k00+w00;
    std::uint32_t h04=z00+d00;
    std::uint32_t d04=z00+s3(a00)+maj(a00,b00,c00);
    std::uint32_t z01=g00+s2(h04)+ch(h04,e00,f00)+k01+w01;
    std::uint32_t g04=z01+c00;
    std::uint32_t c04=z01+s3(d04)+maj(d04,a00,b00);
    std::uint32_t z02=f00+s2(g04)+ch(g04,h04,e00)+k02+w02;
    std::uint32_t f04=z02+b00;
    std::uint32_t b04=z02+s3(c04)+maj(c04,d04,a00);
    std::uint32_t z03=e00+s2(f04)+ch(f04,g04,h04)+k03+w03;
    std::uint32_t e04=z03+a00;
    std::uint32_t a04=z03+s3(b04)+maj(b04,c04,d04);
    const std::uint32_t k04=0x3956c25b;
    const std::uint32_t k05=0x59f111f1;
    const std::uint32_t k06=0x923f82a4;
    const std::uint32_t k07=0xab1c5ed5;
    std::uint32_t w04=0x00000000;
    std::uint32_t w05=0x00000000;
    std::uint32_t w06=0x00000000;
    std::uint32_t w07=0x00000000;
    std::uint32_t z04=h04+s2(e04)+ch(e04,f04,g04)+k04+w04;
    std::uint32_t h08=z04+d04;
    std::uint32_t d08=z04+s3(a04)+maj(a04,b04,c04);
    std::uint32_t z05=g04+s2(h08)+ch(h08,e04,f04)+k05+w05;
    std::uint32_t g08=z05+c04;
    std::uint32_t c08=z05+s3(d08)+maj(d08,a04,b04);
    std::uint32_t z06=f04+s2(g08)+ch(g08,h08,e04)+k06+w06;
    std::uint32_t f08=z06+b04;
    std::uint32_t b08=z06+s3(c08)+maj(c08,d08,a04);
    std::uint32_t z07=e04+s2(f08)+ch(f08,g08,h08)+k07+w07;
    std::uint32_t e08=z07+a04;
    std::uint32_t a08=z07+s3(b08)+maj(b08,c08,d08);
    const std::uint32_t k08=0xd807aa98;
    const std::uint32_t k09=0x12835b01;
    const std::uint32_t k10=0x243185be;
    const std::uint32_t k11=0x550c7dc3;
    std::uint32_t w08=0x00000000;
    std::uint32_t w09=0x00000000;
    std::uint32_t w10=0x00000000;
    std::uint32_t w11=0x00000000;
    std::uint32_t z08=h08+s2(e08)+ch(e08,f08,g08)+k08+w08;
    std::uint32_t h12=z08+d08;
    std::uint32_t d12=z08+s3(a08)+maj(a08,b08,c08);
    std::uint32_t z09=g08+s2(h12)+ch(h12,e08,f08)+k09+w09;
    std::uint32_t g12=z09+c08;
    std::uint32_t c12=z09+s3(d12)+maj(d12,a08,b08);
    std::uint32_t z10=f08+s2(g12)+ch(g12,h12,e08)+k10+w10;
    std::uint32_t f12=z10+b08;
    std::uint32_t b12=z10+s3(c12)+maj(c12,d12,a08);
    std::uint32_t z11=e08+s2(f12)+ch(f12,g12,h12)+k11+w11;
    std::uint32_t e12=z11+a08;
    std::uint32_t a12=z11+s3(b12)+maj(b12,c12,d12);
    const std::uint32_t k12=0x72be5d74;
    const std::uint32_t k13=0x80deb1fe;
    const std::uint32_t k14=0x9bdc06a7;
    const std::uint32_t k15=0xc19bf174;
    std::uint32_t w12=0x00000000;
    std::uint32_t w13=0x00000000;
    std::uint32_t w14=0x00000000;
    std::uint32_t w15=0x00000000;
    std::uint32_t z12=h12+s2(e12)+ch(e12,f12,g12)+k12+w12;
    std::uint32_t h16=z12+d12;
    std::uint32_t d16=z12+s3(a12)+maj(a12,b12,c12);
    std::uint32_t z13=g12+s2(h16)+ch(h16,e12,f12)+k13+w13;
    std::uint32_t g16=z13+c12;
    std::uint32_t c16=z13+s3(d16)+maj(d16,a12,b12);
    std::uint32_t z14=f12+s2(g16)+ch(g16,h16,e12)+k14+w14;
    std::uint32_t f16=z14+b12;
    std::uint32_t b16=z14+s3(c16)+maj(c16,d16,a12);
    std::uint32_t z15=e12+s2(f16)+ch(f16,g16,h16)+k15+w15;
    std::uint32_t e16=z15+a12;
    std::uint32_t a16=z15+s3(b16)+maj(b16,c16,d16);
    const std::uint32_t k16=0xe49b69c1;
    const std::uint32_t k17=0xefbe4786;
    const std::uint32_t k18=0x0fc19dc6;
    const std::uint32_t k19=0x240ca1cc;
    std::uint32_t w16=w00+s0(w01)+w09+s1(w14);
    std::uint32_t w17=w01+s0(w02)+w10+s1(w15);
    std::uint32_t w18=w02+s0(w03)+w11+s1(w16);
    std::uint32_t w19=w03+s0(w04)+w12+s1(w17);
    std::uint32_t z16=h16+s2(e16)+ch(e16,f16,g16)+k16+w16;
    std::uint32_t h20=z16+d16;
    std::uint32_t d20=z16+s3(a16)+maj(a16,b16,c16);
    std::uint32_t z17=g16+s2(h20)+ch(h20,e16,f16)+k17+w17;
    std::uint32_t g20=z17+c16;
    std::uint32_t c20=z17+s3(d20)+maj(d20,a16,b16);
    std::uint32_t z18=f16+s2(g20)+ch(g20,h20,e16)+k18+w18;
    std::uint32_t f20=z18+b16;
    std::uint32_t b20=z18+s3(c20)+maj(c20,d20,a16);
    std::uint32_t z19=e16+s2(f20)+ch(f20,g20,h20)+k19+w19;
    std::uint32_t e20=z19+a16;
    std::uint32_t a20=z19+s3(b20)+maj(b20,c20,d20);
    const std::uint32_t k20=0x2de92c6f;
    const std::uint32_t k21=0x4a7484aa;
    const std::uint32_t k22=0x5cb0a9dc;
    const std::uint32_t k23=0x76f988da;
    std::uint32_t w20=w04+s0(w05)+w13+s1(w18);
    std::uint32_t w21=w05+s0(w06)+w14+s1(w19);
    std::uint32_t w22=w06+s0(w07)+w15+s1(w20);
    std::uint32_t w23=w07+s0(w08)+w16+s1(w21);
    std::uint32_t z20=h20+s2(e20)+ch(e20,f20,g20)+k20+w20;
    std::uint32_t h24=z20+d20;
    std::uint32_t d24=z20+s3(a20)+maj(a20,b20,c20);
    std::uint32_t z21=g20+s2(h24)+ch(h24,e20,f20)+k21+w21;
    std::uint32_t g24=z21+c20;
    std::uint32_t c24=z21+s3(d24)+maj(d24,a20,b20);
    std::uint32_t z22=f20+s2(g24)+ch(g24,h24,e20)+k22+w22;
    std::uint32_t f24=z22+b20;
    std::uint32_t b24=z22+s3(c24)+maj(c24,d24,a20);
    std::uint32_t z23=e20+s2(f24)+ch(f24,g24,h24)+k23+w23;
    std::uint32_t e24=z23+a20;
    std::uint32_t a24=z23+s3(b24)+maj(b24,c24,d24);
    const std::uint32_t k24=0x983e5152;
    const std::uint32_t k25=0xa831c66d;
    const std::uint32_t k26=0xb00327c8;
    const std::uint32_t k27=0xbf597fc7;
    std::uint32_t w24=w08+s0(w09)+w17+s1(w22);
    std::uint32_t w25=w09+s0(w10)+w18+s1(w23);
    std::uint32_t w26=w10+s0(w11)+w19+s1(w24);
    std::uint32_t w27=w11+s0(w12)+w20+s1(w25);
    std::uint32_t z24=h24+s2(e24)+ch(e24,f24,g24)+k24+w24;
    std::uint32_t h28=z24+d24;
    std::uint32_t d28=z24+s3(a24)+maj(a24,b24,c24);
    std::uint32_t z25=g24+s2(h28)+ch(h28,e24,f24)+k25+w25;
    std::uint32_t g28=z25+c24;
    std::uint32_t c28=z25+s3(d28)+maj(d28,a24,b24);
    std::uint32_t z26=f24+s2(g28)+ch(g28,h28,e24)+k26+w26;
    std::uint32_t f28=z26+b24;
    std::uint32_t b28=z26+s3(c28)+maj(c28,d28,a24);
    std::uint32_t z27=e24+s2(f28)+ch(f28,g28,h28)+k27+w27;
    std::uint32_t e28=z27+a24;
    std::uint32_t a28=z27+s3(b28)+maj(b28,c28,d28);
    const std::uint32_t k28=0xc6e00bf3;
    const std::uint32_t k29=0xd5a79147;
    const std::uint32_t k30=0x06ca6351;
    const std::uint32_t k31=0x14292967;
    std::uint32_t w28=w12+s0(w13)+w21+s1(w26);
    std::uint32_t w29=w13+s0(w14)+w22+s1(w27);
    std::uint32_t w30=w14+s0(w15)+w23+s1(w28);
    std::uint32_t w31=w15+s0(w16)+w24+s1(w29);
    std::uint32_t z28=h28+s2(e28)+ch(e28,f28,g28)+k28+w28;
    std::uint32_t h32=z28+d28;
    std::uint32_t d32=z28+s3(a28)+maj(a28,b28,c28);
    std::uint32_t z29=g28+s2(h32)+ch(h32,e28,f28)+k29+w29;
    std::uint32_t g32=z29+c28;
    std::uint32_t c32=z29+s3(d32)+maj(d32,a28,b28);
    std::uint32_t z30=f28+s2(g32)+ch(g32,h32,e28)+k30+w30;
    std::uint32_t f32=z30+b28;
    std::uint32_t b32=z30+s3(c32)+maj(c32,d32,a28);
    std::uint32_t z31=e28+s2(f32)+ch(f32,g32,h32)+k31+w31;
    std::uint32_t e32=z31+a28;
    std::uint32_t a32=z31+s3(b32)+maj(b32,c32,d32);
    const std::uint32_t k32=0x27b70a85;
    const std::uint32_t k33=0x2e1b2138;
    const std::uint32_t k34=0x4d2c6dfc;
    const std::uint32_t k35=0x53380d13;
    std::uint32_t w32=w16+s0(w17)+w25+s1(w30);
    std::uint32_t w33=w17+s0(w18)+w26+s1(w31);
    std::uint32_t w34=w18+s0(w19)+w27+s1(w32);
    std::uint32_t w35=w19+s0(w20)+w28+s1(w33);
    std::uint32_t z32=h32+s2(e32)+ch(e32,f32,g32)+k32+w32;
    std::uint32_t h36=z32+d32;
    std::uint32_t d36=z32+s3(a32)+maj(a32,b32,c32);
    std::uint32_t z33=g32+s2(h36)+ch(h36,e32,f32)+k33+w33;
    std::uint32_t g36=z33+c32;
    std::uint32_t c36=z33+s3(d36)+maj(d36,a32,b32);
    std::uint32_t z34=f32+s2(g36)+ch(g36,h36,e32)+k34+w34;
    std::uint32_t f36=z34+b32;
    std::uint32_t b36=z34+s3(c36)+maj(c36,d36,a32);
    std::uint32_t z35=e32+s2(f36)+ch(f36,g36,h36)+k35+w35;
    std::uint32_t e36=z35+a32;
    std::uint32_t a36=z35+s3(b36)+maj(b36,c36,d36);
    const std::uint32_t k36=0x650a7354;
    const std::uint32_t k37=0x766a0abb;
    const std::uint32_t k38=0x81c2c92e;
    const std::uint32_t k39=0x92722c85;
    std::uint32_t w36=w20+s0(w21)+w29+s1(w34);
    std::uint32_t w37=w21+s0(w22)+w30+s1(w35);
    std::uint32_t w38=w22+s0(w23)+w31+s1(w36);
    std::uint32_t w39=w23+s0(w24)+w32+s1(w37);
    std::uint32_t z36=h36+s2(e36)+ch(e36,f36,g36)+k36+w36;
    std::uint32_t h40=z36+d36;
    std::uint32_t d40=z36+s3(a36)+maj(a36,b36,c36);
    std::uint32_t z37=g36+s2(h40)+ch(h40,e36,f36)+k37+w37;
    std::uint32_t g40=z37+c36;
    std::uint32_t c40=z37+s3(d40)+maj(d40,a36,b36);
    std::uint32_t z38=f36+s2(g40)+ch(g40,h40,e36)+k38+w38;
    std::uint32_t f40=z38+b36;
    std::uint32_t b40=z38+s3(c40)+maj(c40,d40,a36);
    std::uint32_t z39=e36+s2(f40)+ch(f40,g40,h40)+k39+w39;
    std::uint32_t e40=z39+a36;
    std::uint32_t a40=z39+s3(b40)+maj(b40,c40,d40);
    const std::uint32_t k40=0xa2bfe8a1;
    const std::uint32_t k41=0xa81a664b;
    const std::uint32_t k42=0xc24b8b70;
    const std::uint32_t k43=0xc76c51a3;
    std::uint32_t w40=w24+s0(w25)+w33+s1(w38);
    std::uint32_t w41=w25+s0(w26)+w34+s1(w39);
    std::uint32_t w42=w26+s0(w27)+w35+s1(w40);
    std::uint32_t w43=w27+s0(w28)+w36+s1(w41);
    std::uint32_t z40=h40+s2(e40)+ch(e40,f40,g40)+k40+w40;
    std::uint32_t h44=z40+d40;
    std::uint32_t d44=z40+s3(a40)+maj(a40,b40,c40);
    std::uint32_t z41=g40+s2(h44)+ch(h44,e40,f40)+k41+w41;
    std::uint32_t g44=z41+c40;
    std::uint32_t c44=z41+s3(d44)+maj(d44,a40,b40);
    std::uint32_t z42=f40+s2(g44)+ch(g44,h44,e40)+k42+w42;
    std::uint32_t f44=z42+b40;
    std::uint32_t b44=z42+s3(c44)+maj(c44,d44,a40);
    std::uint32_t z43=e40+s2(f44)+ch(f44,g44,h44)+k43+w43;
    std::uint32_t e44=z43+a40;
    std::uint32_t a44=z43+s3(b44)+maj(b44,c44,d44);
    const std::uint32_t k44=0xd192e819;
    const std::uint32_t k45=0xd6990624;
    const std::uint32_t k46=0xf40e3585;
    const std::uint32_t k47=0x106aa070;
    std::uint32_t w44=w28+s0(w29)+w37+s1(w42);
    std::uint32_t w45=w29+s0(w30)+w38+s1(w43);
    std::uint32_t w46=w30+s0(w31)+w39+s1(w44);
    std::uint32_t w47=w31+s0(w32)+w40+s1(w45);
    std::uint32_t z44=h44+s2(e44)+ch(e44,f44,g44)+k44+w44;
    std::uint32_t h48=z44+d44;
    std::uint32_t d48=z44+s3(a44)+maj(a44,b44,c44);
    std::uint32_t z45=g44+s2(h48)+ch(h48,e44,f44)+k45+w45;
    std::uint32_t g48=z45+c44;
    std::uint32_t c48=z45+s3(d48)+maj(d48,a44,b44);
    std::uint32_t z46=f44+s2(g48)+ch(g48,h48,e44)+k46+w46;
    std::uint32_t f48=z46+b44;
    std::uint32_t b48=z46+s3(c48)+maj(c48,d48,a44);
    std::uint32_t z47=e44+s2(f48)+ch(f48,g48,h48)+k47+w47;
    std::uint32_t e48=z47+a44;
    std::uint32_t a48=z47+s3(b48)+maj(b48,c48,d48);
    const std::uint32_t k48=0x19a4c116;
    const std::uint32_t k49=0x1e376c08;
    const std::uint32_t k50=0x2748774c;
    const std::uint32_t k51=0x34b0bcb5;
    std::uint32_t w48=w32+s0(w33)+w41+s1(w46);
    std::uint32_t w49=w33+s0(w34)+w42+s1(w47);
    std::uint32_t w50=w34+s0(w35)+w43+s1(w48);
    std::uint32_t w51=w35+s0(w36)+w44+s1(w49);
    std::uint32_t z48=h48+s2(e48)+ch(e48,f48,g48)+k48+w48;
    std::uint32_t h52=z48+d48;
    std::uint32_t d52=z48+s3(a48)+maj(a48,b48,c48);
    std::uint32_t z49=g48+s2(h52)+ch(h52,e48,f48)+k49+w49;
    std::uint32_t g52=z49+c48;
    std::uint32_t c52=z49+s3(d52)+maj(d52,a48,b48);
    std::uint32_t z50=f48+s2(g52)+ch(g52,h52,e48)+k50+w50;
    std::uint32_t f52=z50+b48;
    std::uint32_t b52=z50+s3(c52)+maj(c52,d52,a48);
    std::uint32_t z51=e48+s2(f52)+ch(f52,g52,h52)+k51+w51;
    std::uint32_t e52=z51+a48;
    std::uint32_t a52=z51+s3(b52)+maj(b52,c52,d52);
    const std::uint32_t k52=0x391c0cb3;
    const std::uint32_t k53=0x4ed8aa4a;
    const std::uint32_t k54=0x5b9cca4f;
    const std::uint32_t k55=0x682e6ff3;
    std::uint32_t w52=w36+s0(w37)+w45+s1(w50);
    std::uint32_t w53=w37+s0(w38)+w46+s1(w51);
    std::uint32_t w54=w38+s0(w39)+w47+s1(w52);
    std::uint32_t w55=w39+s0(w40)+w48+s1(w53);
    std::uint32_t z52=h52+s2(e52)+ch(e52,f52,g52)+k52+w52;
    std::uint32_t h56=z52+d52;
    std::uint32_t d56=z52+s3(a52)+maj(a52,b52,c52);
    std::uint32_t z53=g52+s2(h56)+ch(h56,e52,f52)+k53+w53;
    std::uint32_t g56=z53+c52;
    std::uint32_t c56=z53+s3(d56)+maj(d56,a52,b52);
    std::uint32_t z54=f52+s2(g56)+ch(g56,h56,e52)+k54+w54;
    std::uint32_t f56=z54+b52;
    std::uint32_t b56=z54+s3(c56)+maj(c56,d56,a52);
    std::uint32_t z55=e52+s2(f56)+ch(f56,g56,h56)+k55+w55;
    std::uint32_t e56=z55+a52;
    std::uint32_t a56=z55+s3(b56)+maj(b56,c56,d56);
    const std::uint32_t k56=0x748f82ee;
    const std::uint32_t k57=0x78a5636f;
    const std::uint32_t k58=0x84c87814;
    const std::uint32_t k59=0x8cc70208;
    std::uint32_t w56=w40+s0(w41)+w49+s1(w54);
    std::uint32_t w57=w41+s0(w42)+w50+s1(w55);
    std::uint32_t w58=w42+s0(w43)+w51+s1(w56);
    std::uint32_t w59=w43+s0(w44)+w52+s1(w57);
    std::uint32_t z56=h56+s2(e56)+ch(e56,f56,g56)+k56+w56;
    std::uint32_t h60=z56+d56;
    std::uint32_t d60=z56+s3(a56)+maj(a56,b56,c56);
    std::uint32_t z57=g56+s2(h60)+ch(h60,e56,f56)+k57+w57;
    std::uint32_t g60=z57+c56;
    std::uint32_t c60=z57+s3(d60)+maj(d60,a56,b56);
    std::uint32_t z58=f56+s2(g60)+ch(g60,h60,e56)+k58+w58;
    std::uint32_t f60=z58+b56;
    std::uint32_t b60=z58+s3(c60)+maj(c60,d60,a56);
    std::uint32_t z59=e56+s2(f60)+ch(f60,g60,h60)+k59+w59;
    std::uint32_t e60=z59+a56;
    std::uint32_t a60=z59+s3(b60)+maj(b60,c60,d60);
    const std::uint32_t k60=0x90befffa;
    const std::uint32_t k61=0xa4506ceb;
    const std::uint32_t k62=0xbef9a3f7;
    const std::uint32_t k63=0xc67178f2;
    std::uint32_t w60=w44+s0(w45)+w53+s1(w58);
    std::uint32_t w61=w45+s0(w46)+w54+s1(w59);
    std::uint32_t w62=w46+s0(w47)+w55+s1(w60);
    std::uint32_t w63=w47+s0(w48)+w56+s1(w61);
    std::uint32_t z60=h60+s2(e60)+ch(e60,f60,g60)+k60+w60;
    std::uint32_t h64=z60+d60;
    std::uint32_t d64=z60+s3(a60)+maj(a60,b60,c60);
    std::uint32_t z61=g60+s2(h64)+ch(h64,e60,f60)+k61+w61;
    std::uint32_t g64=z61+c60;
    std::uint32_t c64=z61+s3(d64)+maj(d64,a60,b60);
    std::uint32_t z62=f60+s2(g64)+ch(g64,h64,e60)+k62+w62;
    std::uint32_t f64=z62+b60;
    std::uint32_t b64=z62+s3(c64)+maj(c64,d64,a60);
    std::uint32_t z63=e60+s2(f64)+ch(f64,g64,h64)+k63+w63;
    std::uint32_t e64=z63+a60;
    std::uint32_t a64=z63+s3(b64)+maj(b64,c64,d64);
    std::uint32_t a65=a00+a64;
    std::uint32_t b65=b00+b64;
    std::uint32_t c65=c00+c64;
    std::uint32_t d65=d00+d64;
    std::uint32_t e65=e00+e64;
    std::uint32_t f65=f00+f64;
    std::uint32_t g65=g00+g64;
    std::uint32_t h65=h00+h64;
    std::cout<<toStringRound( 0,a00,b00,c00,d00,e00,f00,g00,h00)<<'\n';
    std::cout<<toStringRound( 4,a04,b04,c04,d04,e04,f04,g04,h04)<<'\n';
    std::cout<<toStringRound( 8,a08,b08,c08,d08,e08,f08,g08,h08)<<'\n';
    std::cout<<toStringRound(12,a12,b12,c12,d12,e12,f12,g12,h12)<<'\n';
    std::cout<<toStringRound(16,a16,b16,c16,d16,e16,f16,g16,h16)<<'\n';
    std::cout<<toStringRound(20,a20,b20,c20,d20,e20,f20,g20,h20)<<'\n';
    std::cout<<toStringRound(24,a24,b24,c24,d24,e24,f24,g24,h24)<<'\n';
    std::cout<<toStringRound(28,a28,b28,c28,d28,e28,f28,g28,h28)<<'\n';
    std::cout<<toStringRound(32,a32,b32,c32,d32,e32,f32,g32,h32)<<'\n';
    std::cout<<toStringRound(36,a36,b36,c36,d36,e36,f36,g36,h36)<<'\n';
    std::cout<<toStringRound(40,a40,b40,c40,d40,e40,f40,g40,h40)<<'\n';
    std::cout<<toStringRound(44,a44,b44,c44,d44,e44,f44,g44,h44)<<'\n';
    std::cout<<toStringRound(48,a48,b48,c48,d48,e48,f48,g48,h48)<<'\n';
    std::cout<<toStringRound(52,a52,b52,c52,d52,e52,f52,g52,h52)<<'\n';
    std::cout<<toStringRound(56,a56,b56,c56,d56,e56,f56,g56,h56)<<'\n';
    std::cout<<toStringRound(60,a60,b60,c60,d60,e60,f60,g60,h60)<<'\n';
    std::cout<<toStringRound(64,a64,b64,c64,d64,e64,f64,g64,h64)<<'\n';
    std::cout<<toStringRound(65,a65,b65,c65,d65,e65,f65,g65,h65)<<'\n';
}
