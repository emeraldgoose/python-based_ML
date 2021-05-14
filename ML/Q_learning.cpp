#include <iostream>

#define endl '\n'

#define MAX2(a,b) ((a) > (b) ? (a) : (b))
#define MAX3(a,b,c) (MAX2(MAX2(a,b), (c)))
#define MAX4(a,b,c,d) (MAX2(MAX3(a,b,c), (d)))

class CellData {
    public:
        double q_[4] = {0.0, 0.0, 0.0, 0.0}; // up, down, left, right
        double reward_ = 0.0;

        CellData()
        {}

        double getMaxQ() {
            return MAX4(q_[0], q_[1], q_[2], q_[3]);
        }
};

class GridWorld { // 격자 구조
    public:
        int i_res_, j_res_; // 크기
        CellData *q_arr2d_ = nullptr; // 실제 데이터는 동적할당
        
        GridWorld(const int& i_res, const int& j_res) // 생성자
            : i_res_(i_res), j_res_(j_res)
        {
            q_arr2d_ = new CellData[i_res*j_res];
        }

        ~GridWorld() // 소멸자
        {
            delete q_arr2d_;
            q_arr2d_=0;
        }

        CellData& getCell(const int& i, const int& j) {
            return q_arr2d_[i + i_res_ * j];
        }

        bool isInside(const int& i, const int& j) { // 격자 밖으로 나가지 않게
            if(i<0) return false;
            if(i>=i_res_) return false;

            if(j<0) return false;
            if(j>=j_res_) return false;

            return true;
        }

        void printSigned(const float& v) {
            if(v > 0.0f) printf("+%1.1f", v);
            else if(v < 0.0f) printf("%1.1f", v);
            else printf(" 0.0");
        }

        void print() {
            for(int j=j_res_-1;j>=0;j--) {
                for(int i=0;i<i_res_;i++) {
                    CellData &cell = getCell(i,j);

                    printf("   "); printSigned(cell.q_[0]); printf("   "); // up
                    printf("   ");
                }
                printf("\n");

                for(int i=0;i<i_res_;i++) {
                    CellData &cell = getCell(i,j);
                    printSigned(cell.q_[2]); printf("   "); printSigned(cell.q_[3]); // left, right
                    printf("  ");
                }
                printf("\n");

                for(int i=0;i<i_res_;i++) {
                    CellData &cell = getCell(i,j);
                    printf("   "); printSigned(cell.q_[1]); printf("   "); // down
                    printf("   ");
                }

                printf("\n");
            }
        }
};

class Agent {
    public:
        int i_, j_; // position in grid world
        double reward_; // reward sum

        Agent()
            : i_(0), j_(0), reward_(0.0)
        {}
};

int main() {
    std::cout<<"Hello, grid word!"<<endl;

    const int world_res_i = 3, world_res_j = 2;

    GridWorld world(world_res_i,world_res_j);

    // reference return type
    // world.getCell(i,j).reward_ = 10;

    // CellData &old_cell = world.getCell(i,j);
    // old_cell.reward_ = 10;

    // for(int j=0;j<world_res_j;j++) {
    //     for(int i=0;i<world_res_i;i++) {
    //         world.getCell(i,j).reward_=-0.1;
    //     }
    // }

    world.getCell(2,1).reward_=1.0;
    world.getCell(2,0).reward_=-1.0;

    Agent my_agent;

    // world.print();

    for(int t=0;t<1000000;t++) {
        const int action = rand() % 4; // random policy

        int i = my_agent.i_, j = my_agent.j_;
        int i_old = i, j_old = j;

        switch (action)
        {
        case 0:
            j++; // up
            break;
        case 1:
            j--; // down
            break;
        case 2:
            i--; // left
            break;
        case 3:
            i++; // right
            break;
        default:
            break;
        }

        if(world.isInside(i,j) == true) { // move robot if available
            // move agent
            my_agent.i_=i, my_agent.j_=j;

            // update reward (r_t)
            if(i==2 && j==1) { // good place
                my_agent.reward_+=1.0;
            }
            else if(i==2 && j==0) { // bad place
                my_agent.reward_-=1.0;
            }
            else { // move penalty -1
                my_agent.reward_-=0.1;
            }
            
            // update a values of previous cell (q_t)
            world.getCell(i_old,j_old).q_[action]=my_agent.reward_+world.getCell(i,j).getMaxQ();
            
            // reset if agent is in final cell
            if(i==2) my_agent.i_=0, my_agent.j_=0, my_agent.reward_=0;
        }
        else {
            // you may give negative reward (penalty) to agent.
            world.getCell(i_old,j_old).q_[action]=-1.0;
            
            // reset agent
            my_agent.i_=0, my_agent.j_=0, my_agent.reward_=0;
        }
        
        // std::cout<<"Agent status "<<my_agent.i_<<' '<<my_agent.j_<<endl;
        // std::cout<<"action "<<action<<endl;
    }

    world.print();

    return 0;
}