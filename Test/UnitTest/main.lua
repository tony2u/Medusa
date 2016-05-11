function main()
  do

local a= Test();
print(a);
print(a.X);
a:Foo();
cl=a:Clone2();
print(cl.X);

cl2=a:Clone3();
print(cl2.X);

end


end

main()

d={}
d[3]=2
a={}
a.b={}
a.b['str']={}
a.b['str'][2]={}
a.b['str'][2].c=555

function foo()
  print("foo");
end

function add(a, b)
  return a + b
end

function sum_and_difference(a, b)
  return (a+b), (a-b);
end

function bar()
  return 4, true, "hi"
end

mytable = {}
function mytable.foo()
    return 4
end
outHandler={}

function SetHandler(func)
  outHandler=func;
end

function CallHandler(a,b)
  return outHandler(a,b)
  end

--my={}
--my.a={}
--my.a.b="abc"
