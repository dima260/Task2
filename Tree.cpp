#include <iostream>
#include <iomanip>

class BDP
{
private:
    int value; // тестовые данные
    BDP* left;
    BDP* right;

public:
    BDP* root; // адрес корня дерева
    void createTree(); // создание БДП
    void outputTree(BDP* root); // вывод на экран вершин БДП
    void insertElement(BDP obj, BDP*& root); // включение элемента в БДП
    void deleteTree(BDP*& root); // удаление БДП
    void deleteElement(int studentID, BDP*& root); // удаление по ключу
    void searchElement(int studentID_2, BDP* root); // поиск элемента по ключу
};

int main()
{
    setlocale(LC_ALL, "Russian");
    int menu = 0;

    BDP* first = new BDP;

    while (menu != 6)
    {
        std::cout << "Выберите вариант:" << std::endl;
        std::cout << "1.Заполнить БД\n"
            << "2.Вывести на экран БД\n"
            << "3.Поиск элемента из БД по ключу\n"
            << "4.Удаление элемента из БД по ключу\n"
            << "5.Удалить БД\n"
            << "6.Выйти" << std::endl;
        std::cout << ">>> ";
        std::cin >> menu;

        switch (menu)
        {
        case 1:
        {
            std::cout << "\n\nСоздание дерева." << std::endl;
            first->createTree();
            std::cout << std::endl << std::endl;
            break;
        }
        case 2:
        {
            std::cout << "\n\nВывод дерева:" << std::endl;
            first->outputTree(first->root);
            std::cout << std::endl << std::endl << std::endl;
            break;
        }
        case 3:
        {
            std::cout << "\n\nПоиск узла по значению.";
            std::cout << " Введите значение узла: ";
            int var;
            std::cin >> var;
            first->searchElement(var, first->root);
            std::cout << std::endl << std::endl << std::endl;
            break;
        }
        case 4:
        {
            std::cout << "\n\nВведите значение узла, который нужно удалить: ";
            int var;
            std::cin >> var;
            first->deleteElement(var, first->root);

            std::cout << "Дерево после удаления узла: ";
            first->outputTree(first->root);

            std::cout << std::endl << std::endl << std::endl;
            break;
        }
        case 5:
        {
            std::cout << "\n\nДерево удалено." << std::endl;
            first->deleteTree(first->root);
            std::cout << std::endl << std::endl;
            break;
        }
        case 6:
        {
            exit(EXIT_SUCCESS);
            break;
        }
        default:
        {
            std::cout << "Введите 1-6!" << std::endl;
            break;
        }
        }
    }

    return 0;
}

void BDP::outputTree(BDP* root) // вывод дерева
{
    // p - адресс корня дерева
    if (root != nullptr)
    {
        outputTree(root->left);
        std::cout << " -> " << root->value;
        outputTree(root->right);
    }
}

void BDP::insertElement(BDP obj, BDP*& root) // obj - ключаемая вершина, root - адрес корня дерева
{
    if (root == nullptr)
    {
        root = new BDP;
        root->value = obj.value;
        root->left = nullptr;
        root->right = nullptr;
    }
    else
    {
        if (obj.value < root->value)
            insertElement(obj, root->left);
        else
        {
            if (obj.value > root->value)
                insertElement(obj, root->right);
        }
    }
}

void BDP::createTree()
{
    BDP obj; // объект класса BDP
    root = nullptr;

    int n; // количество Node
    std::cout << "Введите количство узлов дерева: ";
    std::cin >> n;

    for (int i = 1; i <= n; i++) // n - количество вершин
    {
        std::cout << "Введите значение: ";
        std::cin >> obj.value; // ввод строки с клавиатуры
        insertElement(obj, root); // включение вершины в БДП
    }
}

void BDP::searchElement(int valueSearch, BDP* root)
{
    if (root == nullptr)
    {
        std::cout << "Дерево не существует.";
    }
    else
    {
        while ((root != nullptr) && (root->value != valueSearch))
        {
            if (root->value < valueSearch)
            {
                root = root->right;
            }
            else
            {
                root = root->left;
            }
        }
        if (root == nullptr)
        {
            std::cout << "Элемент не найден.";
        }
        else
        {
            std::cout << " -> " << root->value;
        }
    }
}

void BDP::deleteTree(BDP*& p)
{
    // p - адрес корня дерева
    if (p != nullptr)
    {
        deleteTree(p->left);
        deleteTree(p->right);
        delete p;
        p = nullptr;
    }
}

void BDP::deleteElement(int value, BDP*& root) // удаление по ключу
{
    if (root == nullptr)
    {
        std::cout << "Элемент не найден";
    }
    else
    {
        if (value < root->value)
        {
            deleteElement(value, root->left); // искать в левом поддереве
        }
        else
        {
            if (value > root->value)
            {
                deleteElement(value, root->right); // искать в правом поддереве
            }
            else
            { //элемент найден
                BDP* currentNode = root;
                if (currentNode->right == nullptr)
                {
                    root = currentNode->left;
                }
                else
                {
                    if (currentNode->left == nullptr)
                    {
                        root = currentNode->right;
                    }
                    else delete(currentNode->left);
                }
                delete currentNode; //удаление элемента из ДП
            }
        }
    }
}
