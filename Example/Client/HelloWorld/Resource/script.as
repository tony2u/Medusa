// Let's include another script file
#include "scriptinclude.as"

interface IRole
{
	void Attack();
}

class Hero:IRole
{
	void Attack()
	{
		print("attack");
	}
	int mHP;
}

void MyPass(MyType my)
{
	my.Test();
}

void main()
{
	Hero hero;
	
}
