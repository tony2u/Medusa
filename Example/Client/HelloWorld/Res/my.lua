--print(g_test:is_base())
--print(g_test.mTest)
--g_test.mTest=456
--print(g_test.mTest)

print(haha)
print(haha.value)
print(haha.inside)
print(haha.inside.value)

haha.test = "input from lua"
--temp = sub(4)
--print(temp.mTest)

--print("cpp_int = "..cpp_int)
lua_int = 200
width=100;

background={r=4,g=0.4,b=0.5,}

function func_Add(x, y)
	return x+y;
end

function printWidth(arg)
	print(arg:is_base());
end

function createTest(arg)
	return sub(arg);
end

function print_table(arg)
	print("arg = ", arg)
	print("arg.name = ", arg.name)
end

-- LuaTinker 에게 테이블을 넘긴다.
function return_table(arg)
	local ret = {}
	ret.name = arg
	return ret
end

function Update(arg)
	print("dt = ", arg)
end