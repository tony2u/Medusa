namespace Medusa.Siren.Schema
{
    public abstract class BaseSirenCustomType : SirenType
    {
        protected BaseSirenCustomType(string name="") : base(name)
        {
        }

        public override bool IsBuildIn => false;
        public override bool IsTemplate => false;

        protected BaseSirenCustomType mParent;
        public BaseSirenCustomType Parent
        {
            get { return mParent; }
            set
            {
                if (mParent != value)
                {
                    mParent = value;
                    if (mParent != null)
                    {
                        FullName = mParent.FullName + "." + Name;
                    }
                    else
                    {
                        FullName = Name;
                    }

                }
            }
        }
        public string Directory { get; protected set; }

        public abstract void AddAttribute(string name, string val);
        public abstract void SetAttribute(string val);


    }
}
