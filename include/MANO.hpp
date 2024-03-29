#include <vector>

namespace mchand
{
    class MANO
    {
    public:
        static void Init();

        static std::vector<std::pair<int, int>> skeleton;
        static std::vector<std::vector<int>> rhand_faces;

        static std::vector<std::vector<int>> lhand_faces;
        static std::vector<int> rrhand_faces;
        static std::vector<int> llhand_faces;
    private:
    };
}
