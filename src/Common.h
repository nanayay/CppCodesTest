#pragma once

namespace Common {
    class Test {
    protected:
        virtual bool prepare();
        virtual bool run() = 0;
        virtual bool shutdown();

    public:
        void Execute()
        {
            prepare();
            run();
            shutdown();
        }
    };
    bool Test::prepare()
    {
        return true;
    }

    bool Test::shutdown()
    {
        return true;
    }

    bool Test::run()
    {
        return true;
    }
}
