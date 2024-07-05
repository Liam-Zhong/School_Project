/*  A2041240-程序设计实践
    选题：

    参考题九——图示冒泡排序

    功能：

    支持图形界面和文本方式展示排序过程，排序算法包括冒泡排序、快排、选择排序和插入排序
    用户运行程序后可选择展示方式，同时可选择随机20个数据排序和自定义10个数据排序
    输入数据后可选择不同的排序算法

 */

//
// Created by Chlzhong on 5/24/2024.
//
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
#include <sstream>
#include <iomanip>

//常量定义

// 窗口宽度
const int WINDOW_WIDTH = 1200;
// 窗口高度
const int WINDOW_HEIGHT = 800;
// 蓝色常量
const sf::Color BLUE(135, 206, 250);

// 排序可视化类
class SortVisualizer
    {
    private:
        // 数组
        std::vector<int> arr;
        // 窗口指针
        sf::RenderWindow *window;
        // 当前算法
        std::string currentAlgorithm;
        // 比较次数
        int comparisons;
        // 交换次数
        int swaps;
        // 开始时间
        std::chrono::steady_clock::time_point startTime;
        // 排序标志
        bool sorting;
        // 图形模式标志
        bool graphicalMode;
        // 初始数组
        std::vector<int> initialArray;

        // 绘制柱状图
        void drawBars(int highlight1 = -1, int highlight2 = -1)
            {
                // 如果不是图形模式或窗口为空则返回
                if (!graphicalMode || window == nullptr) {
                    return;
                }

                // 清除窗口
                window->clear(sf::Color(250, 250, 25011));

                // 柱状图宽度
                float barWidth = static_cast<float>(WINDOW_WIDTH) / arr.size();
                // 缩放因子
                float scaleFactor = static_cast<float>(WINDOW_HEIGHT) / *std::max_element(arr.begin(), arr.end());

                // 绘制每个柱状图
                for (size_t i = 0; i < arr.size(); ++i) {
                    sf::RectangleShape bar(sf::Vector2f(barWidth - 1, arr[i] * scaleFactor));
                    bar.setPosition(i * barWidth, WINDOW_HEIGHT - arr[i] * scaleFactor);

                    if (i == highlight1 || i == highlight2) {
                        bar.setFillColor(sf::Color(250, 128, 114));
                    } else {
                        bar.setFillColor(BLUE);
                    }

                    window->draw(bar);
                }

                drawStats();
                window->display();
            }

        // 绘制统计信息
        void drawStats()
            {
                // 如果不是图形模式或窗口为空则返回
                if (!graphicalMode || window == nullptr) {
                    return;
                }

                // 输出统计信息
                std::ostringstream stats;
                stats << "Algorithm: " << currentAlgorithm << "\n"
                        << "Comparisons: " << comparisons << "\n"
                        << "Swaps: " << swaps << "\n"
                        << "Time: " << std::fixed << std::setprecision(2)
                        << std::chrono::duration<double>(std::chrono::steady_clock::now() - startTime).count() << "s";

                sf::Text statsText;
                // statsText.setFont(font);
                statsText.setString(stats.str());
                statsText.setCharacterSize(20);
                statsText.setFillColor(sf::Color::White);
                statsText.setPosition(10, 10);
                window->draw(statsText);
            }

        // 交换元素
        void swap(int &a, int &b)
            {
                int temp = a;
                a = b;
                b = temp;
                swaps++;
            }

        // 重置统计信息
        void resetStats()
            {
                comparisons = 0;
                swaps = 0;
                startTime = std::chrono::steady_clock::now();
            }

        // 显示文本数组
        void displayTextArray(const std::vector<int> &array, const std::string &label)
            {
                std::cout << label << ": ";
                for (size_t i = 0; i < array.size(); ++i) {
                    std::cout << std::setw(4) << array[i];
                }
                std::cout << std::endl;
            }

        // 显示文本统计信息
        void displayTextStats()
            {
                if (graphicalMode) {
                    return;
                }

                std::cout << "Algorithm: " << currentAlgorithm << " | "
                        << "Comparisons: " << comparisons << " | "
                        << "Swaps: " << swaps << " | "
                        << "Time: " << std::fixed << std::setprecision(2)
                        << std::chrono::duration<double>(std::chrono::steady_clock::now() - startTime).count() << "s\n";
            }

    public:
        // 构造函数
        SortVisualizer() : window(nullptr), sorting(false), graphicalMode(false)
            {
                // if (!font.loadFromFile("arial.ttf")) {
                //   std::cout << "Error loading font" << std::endl;
                //}
            }

        // 析构函数
        ~SortVisualizer()
            {
                if (window != nullptr) {
                    delete window;
                }
            }

        // 设置图形模式
        void setGraphicalMode(bool mode)
            {
                graphicalMode = mode;
                if (graphicalMode && window == nullptr) {
                    window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                                                  "Optimized Sorting Visualizer");
                    window->setFramerateLimit(10);
                }
            }

        // 生成随机数组
        void generateRandomArray(int size)
            {
                arr.clear();
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(1, 100);

                for (int i = 0; i < size; ++i) {
                    arr.push_back(dis(gen));
                }
                initialArray = arr;
            }

        // 获取用户输入
        void getUserInput(int size)
            {
                arr.clear();
                std::cout << "Enter " << size << " integers:\n";
                for (int i = 0; i < size; ++i) {
                    int num;
                    std::cin >> num;
                    arr.push_back(num);
                }
                initialArray = arr;
            }

        // 冒泡排序
        void bubbleSort()
            {
                currentAlgorithm = "Bubble Sort";
                resetStats();
                sorting = true;

                if (!graphicalMode) {
                    displayTextArray(initialArray, "Initial array");
                }

                for (size_t i = 0; i < arr.size() && sorting; ++i) {
                    bool swapped = false;
                    for (size_t j = 0; j < arr.size() - i - 1 && sorting; ++j) {
                        comparisons++;
                        if (graphicalMode) {
                            drawBars(j, j + 1);
                        }
                        if (arr[j] > arr[j + 1]) {
                            swap(arr[j], arr[j + 1]);
                            swapped = true;
                        }
                    }
                    if (!graphicalMode) {
                        displayTextArray(arr, "Current array after pass " + std::to_string(i + 1));
                        displayTextStats();
                    }
                    if (!swapped) {
                        break;
                    }
                }
                if (graphicalMode) {
                    drawBars();
                } else {
                    displayTextArray(arr, "Sorted array ");
                    displayTextStats();
                }
                sorting = false;
            }

        // 快速排序
        void quickSort(int low, int high)
            {
                if (low < high && sorting) {
                    int pi = partition(low, high);
                    quickSort(low, pi - 1);
                    quickSort(pi + 1, high);
                }
            }

        // 分区函数
        int partition(int low, int high)
            {
                int pivot = arr[high];
                int i = low - 1;

                for (int j = low; j <= high - 1 && sorting; ++j) {
                    comparisons++;
                    if (graphicalMode) {
                        drawBars(j, high);
                    }
                    if (arr[j] < pivot) {
                        ++i;
                        swap(arr[i], arr[j]);
                    }
                }
                swap(arr[i + 1], arr[high]);
                return i + 1;
            }

        // 运行快速排序
        void runQuickSort()
            {
                currentAlgorithm = "Quick Sort";
                resetStats();
                sorting = true;

                if (!graphicalMode) {
                    displayTextArray(initialArray, "Initial array");
                }

                quickSort(0, arr.size() - 1);

                if (graphicalMode) {
                    drawBars();
                } else {
                    displayTextArray(arr, "Sorted array ");
                    displayTextStats();
                }
                sorting = false;
            }

        // 选择排序
        void selectionSort()
            {
                currentAlgorithm = "Selection Sort";
                resetStats();
                sorting = true;

                if (!graphicalMode) {
                    displayTextArray(initialArray, "Initial array");
                }

                for (size_t i = 0; i < arr.size() && sorting; ++i) {
                    size_t minIdx = i;
                    for (size_t j = i + 1; j < arr.size() && sorting; ++j) {
                        comparisons++;
                        if (graphicalMode) {
                            drawBars(minIdx, j);
                        }
                        if (arr[j] < arr[minIdx]) {
                            minIdx = j;
                        }
                    }
                    if (minIdx != i) {
                        swap(arr[i], arr[minIdx]);
                    }
                    if (!graphicalMode) {
                        displayTextArray(arr, "Current array after pass " + std::to_string(i + 1));
                        displayTextStats();
                    }
                }
                if (graphicalMode) {
                    drawBars();
                } else {
                    displayTextArray(arr, "Sorted array ");
                    displayTextStats();
                }
                sorting = false;
            }

        // 插入排序
        void insertionSort()
            {
                currentAlgorithm = "Insertion Sort";
                resetStats();
                sorting = true;

                if (!graphicalMode) {
                    displayTextArray(initialArray, "Initial array");
                }

                for (size_t i = 1; i < arr.size() && sorting; ++i) {
                    int key = arr[i];
                    int j = i - 1;
                    while (j >= 0 && arr[j] > key && sorting) {
                        comparisons++;
                        if (graphicalMode) {
                            drawBars(j, j + 1);
                        }
                        arr[j + 1] = arr[j];
                        swaps++;
                        j--;
                    }
                    arr[j + 1] = key;
                    if (!graphicalMode) {
                        displayTextArray(arr, "Current array after pass " + std::to_string(i));
                        displayTextStats();
                    }
                }
                if (graphicalMode) {
                    drawBars();
                } else {
                    displayTextArray(arr, "Sorted array ");
                    displayTextStats();
                }
                sorting = false;
            }

        // 处理事件
        void handleEvents()
            {
                if (!graphicalMode || window == nullptr) {
                    return;
                }

                sf::Event event;
                while (window->pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window->close();
                    }

                    if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Space) {
                            sorting = false;
                        }
                        if (event.key.code == sf::Keyboard::Escape) {
                            window->close();
                        }
                    }
                }
            }

        // 运行可视化
        void run()
            {
                if (graphicalMode && window != nullptr) {
                    while (window->isOpen()) {
                        handleEvents();

                        if (!sorting && !arr.empty()) {
                            drawBars();
                        }
                    }
                }
            }

        // 重置数组
        void reset()
            {
                arr = initialArray;
            }
    };

// 打印指令
void printInstructions()
    {
        std::cout << "Select sorting algorithm:" << std::endl;
        std::cout << "  1 - Bubble Sort" << std::endl;
        std::cout << "  2 - Quick Sort" << std::endl;
        std::cout << "  3 - Selection Sort" << std::endl;
        std::cout << "  4 - Insertion Sort" << std::endl;
        std::cout << "  5 - Reset array" << std::endl;
        std::cout << "  0 - Exit program" << std::endl;
    }

// 主函数
int main()
    {
        SortVisualizer visualizer;

        std::cout << "Select display mode:" << std::endl;
        std::cout << "1 - Graphical mode" << std::endl;
        std::cout << "2 - Text mode" << std::endl;
        int displayMode;
        std::cin >> displayMode;

        visualizer.setGraphicalMode(displayMode == 1);

        std::cout << "Select data input method:" << std::endl;
        std::cout << "1 - Random 20 numbers" << std::endl;
        std::cout << "2 - User-defined 10 numbers" << std::endl;
        int inputMethod;
        std::cin >> inputMethod;

        if (inputMethod == 1) {
            visualizer.generateRandomArray(20);
        } else {
            visualizer.getUserInput(10);
        }

        int choice;
        do {
            printInstructions();
            std::cin >> choice;

            switch (choice) {
                case 1:
                    visualizer.bubbleSort();
                    break;
                case 2:
                    visualizer.runQuickSort();
                    break;
                case 3:
                    visualizer.selectionSort();
                    break;
                case 4:
                    visualizer.insertionSort();
                    break;
                case 5:
                    visualizer.reset();
                    std::cout << "Array reset to initial state." << std::endl;
                    break;
                case 0:
                    std::cout << "Exiting program." << std::endl;
                    break;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
            }
        } while (choice != 0);

        if (displayMode == 1) {
            visualizer.run();
        }

        return 0;
    }
