//YUDHISTIRA
//225150301111029
//THIS SOURCE CODE WAS NOT PLAGIARIZED FROM ANY SOURCE

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <filesystem>

using std::ios;

typedef struct StudentData
{
    std::string nama;
    std::string nim;
    std::vector<std::string> matkul;
    std::vector<float> nilai;
    float rerataNilai;
} StudentData;

class CsvFile
{
    std::string filePath;
    char csvDelim;

public:
    explicit CsvFile(std::string path)
        : filePath(path), csvDelim(',')
    {
    }
    explicit CsvFile(std::string path, char delim)
        : filePath(path), csvDelim(delim)
    {
    }
    size_t findRow(std::string key, int col = 0)
    {
        size_t id = -1;
        std::ifstream file(filePath, ios::in);
        std::string line, word;
        for (size_t i = 0; getline(file, line); i++)
        {
            std::stringstream stream(line);
            for (int j = 0; j <= col && std::getline(stream, word, csvDelim); j++)
                ;
            if (word == key)
            {
                id = i;
                break;
            }
        }
        return id;
    }
    size_t rowCount()
    {
        std::ifstream file;
        size_t count = 0;
        std::string line;

        file.open(filePath, ios::in);
        while (std::getline(file, line))
            count++;
        return count;
    }
    size_t colCount()
    {
        std::ifstream file;
        size_t count = 0;
        std::string line, word;

        file.open(filePath, ios::in);
        std::getline(file, line);
        std::stringstream sline(line);
        while (std::getline(sline, word, csvDelim))
            count++;
        return count;
    }
    std::vector<std::string> getRow(size_t id)
    {
        std::vector<std::string> row;
        std::ifstream file;
        std::string line, word;

        file.open(filePath, ios::in);

        for (int i = 0; i <= id && std::getline(file, line); i++)
            ;

        std::stringstream sline(line);
        while (std::getline(sline, word, csvDelim))
            row.push_back(word);

        return row;
    }
    std::vector<std::string> getRow(std::string key, int col)
    {
        std::vector<std::string> row({});
        std::ifstream file(filePath, ios::in);
        std::string line, word;

        while (std::getline(file, line))
        {
            std::stringstream sline(line);
            for (int i = 0; i <= col && std::getline(sline, word, csvDelim); i++)
                ;
            if (word == key)
            {
                sline.seekg(ios::beg);
                while (std::getline(sline, word, csvDelim))
                    row.push_back(word);

                break;
            }
        }

        return row;
    }
    std::vector<std::string> getCol(size_t id)
    {
        std::vector<std::string> col;
        std::ifstream file;
        std::string line, word;

        file.open(filePath, ios::in);
        while (std::getline(file, line))
        {
            std::stringstream sline(line);
            for (int i = 0; i <= id && std::getline(sline, word, csvDelim); i++)
                ;
            col.push_back(word);
        }
        return col;
    }
    std::string getCell(size_t row, size_t col)
    {
        std::ifstream file(filePath, ios::in);
        std::string line, cell;

        for (int i = 0; i <= row && std::getline(file, line); i++)
            ;
        std::stringstream sline(line);
        for (int i = 0; i <= col && std::getline(sline, cell, csvDelim); i++)
            ;
        return cell;
    }
};

void clear_screen()
{
#if defined(__WIN32__) || defined(WIN32) || defined(_WIN32) || defined(__NT__)
    system("cls");
#elif defined(__APPLE__) || defined(__linux__) || defined(__unix__)
    system("clear -x");
#endif
}

StudentData *getStudentData(std::string nim);

CsvFile *mkA, *mkB, *mkC, *mkD;
const std::string matkul[4] = {"MK-A", "MK-B", "MK-C", "MK-D"};

int main()
{
    {
        
        std::string csvParentDir;

        //confirm the existence of the folder, then the existence of the .csv file(s)
        namespace fs = std::filesystem;
        fs::path csvDirPath = csvParentDir;
        while(!fs::is_directory(csvDirPath) || !fs::exists(csvDirPath/"MK-A.csv"))
        {
            std::cout << "Folder berisi csv (\".\" jika dalam folder ini)\nNama Folder: ";
            std::getline(std::cin, csvParentDir);
            csvDirPath = csvParentDir;
            clear_screen();
            if (!fs::is_directory(csvDirPath))
                std::cout << "folder " << csvDirPath << " tidak ada." << std::endl;
            else if (!fs::exists(csvDirPath/"MK-A.csv"))
                std::cout << "folder " << csvDirPath << " tidak memiliki file .csv" << std::endl;
        }
    
        mkA = new CsvFile(csvParentDir + "/MK-A.csv", ';');
        mkB = new CsvFile(csvParentDir + "/MK-B.csv", ';');
        mkC = new CsvFile(csvParentDir + "/MK-C.csv", ';');
        mkD = new CsvFile(csvParentDir + "/MK-D.csv", ';');
    }

    const std::string manual =
        "Commands:\n\
        mk_mhs \t\t menampilkan daftar matkul (dan nilainya) yang diambil seorang mahasiswa\n\
        mkavg_mhs \t menampilkan nilai rata-rata semua matkul seorang mahasiswa\n\
        top_mk \t\t menampilkan 15 pemegang skor terbaik pada satu mata kuliah\n\
        scrdist_mk \t menampilkan rentang nilai dan jumlah mahasiswa dalam rentang tsb.\n\
        top \t\t menampilkan N pemegang skor tertinggi (berdasarkan nilai rata-rata)\n\
        help \t\t menampilkan panduan ini\n\
        quit \t\t keluar dari program\n";

    std::string command = "";
    std::cout << manual << std::endl;
    std::cout << "program ini tidak diperuntukkan untuk mobile." << std::endl;
    std::cout << "tekan Enter... ";
    std::cin.get();

    while (true)
    {
        clear_screen();
        std::cout << "masukkan perintah: ";
        std::cin >> command;
        //std::cin.ignore();
        if (command == "mk_mhs")
        {
            std::string nim;
            std::cout << "masukkan NIM: ";
            std::cin >> nim;
            std::cin.ignore();
            StudentData *dataMhs = getStudentData(nim);

            std::cout << "NIM:\t" << dataMhs->nim << std::endl;
            std::cout << "Nama:\t" << dataMhs->nama << std::endl;
            std::cout << "Nilai:" << std::endl;
            for (int i = 0; i < dataMhs->matkul.size(); i++)
            {
                std::cout << dataMhs->matkul[i] << ": " << dataMhs->nilai[i] << std::endl;
            }

            delete dataMhs;
        }
        else if (command == "mkavg_mhs")
        {
            std::string nim;
            std::cout << "masukkan NIM: ";
            std::cin >> nim;
            std::cin.ignore();
            StudentData *dataMhs = getStudentData(nim);

            std::cout << "NIM:\t\t\t" << dataMhs->nim << std::endl;
            std::cout << "Nama:\t\t\t" << dataMhs->nama << std::endl;
            std::cout << "Rata-rata nilai:\t" << dataMhs->rerataNilai << std::endl;

            delete dataMhs;
        }
        else if (command == "top_mk")
        {
            std::string mk;
            std::cout << "Matkul:\n\
            MK-A\n\
            MK-B\n\
            MK-C\n\
            MK-D\
            " << std::endl;
            do
            {
                std::cout << "masukkan Matkul: ";
                std::cin >> mk;
                std::cin.ignore();
            } while (mk != "MK-A" && mk != "MK-B" && mk != "MK-C" && mk != "MK-D");

            CsvFile *fDataMk;
            if (mk == "MK-A")
                fDataMk = mkA;
            else if (mk == "MK-B")
                fDataMk = mkB;
            else if (mk == "MK-C")
                fDataMk = mkC;
            else if (mk == "MK-D")
                fDataMk = mkD;

            std::vector<std::string> scores, names, nims;
            scores = fDataMk->getCol(2);
            names = fDataMk->getCol(1);
            nims = fDataMk->getCol(0);

            //{{id, score},...}
            unsigned short topFive[15][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};

            for (int i = 0; i < scores.size(); i++)
            {
                float score = std::stof(scores[i]);
                for (int j = 0; j < 15; j++)
                {
                    if (score > topFive[j][1])
                    {
                        topFive[j][0] = i;
                        topFive[j][1] = score;
                        break;
                    }
                }
            }

            // finally...
            std::cout << "NIM\tNAMA NILAI" << std::endl;
            for (int i = 0; i < 15; i++)
            {
                size_t j = topFive[i][0];
                std::cout << nims[j] << "\t" << names[j] << " " << scores[j];
                std::cout << std::endl;
            }
        }
        else if (command == "scrdist_mk")
        {
            std::string mk;
            std::cout << "Matkul:\n\
            MK-A\n\
            MK-B\n\
            MK-C\n\
            MK-D\
            " << std::endl;
            std::cout << "masukkan Matkul: ";
            do
            {
                std::cin >> mk;
                std::cin.ignore();
            } while (mk != "MK-A" && mk != "MK-B" && mk != "MK-C" && mk != "MK-D");

            unsigned int counts[4] = {0, 0, 0, 0};
            std::vector<std::string> scores;

            if (mk == "MK-A")
                scores = mkA->getCol(2);
            else if (mk == "MK-B")
                scores = mkB->getCol(2);
            else if (mk == "MK-C")
                scores = mkC->getCol(2);
            else if (mk == "MK-D")
                scores = mkD->getCol(2);

            for (size_t i = 0; i < scores.size(); i++)
            {
                float score = std::stof(scores[i]);
                if (score >= 0 && score <= 60)
                {
                    counts[0]++;
                    continue;
                }
                else if (score >= 61 && score <= 75)
                {
                    counts[1]++;
                    continue;
                }
                else if (score >= 76 && score <= 90)
                {
                    counts[2]++;
                    continue;
                }
                else if (score >= 91 && score <= 100)
                {
                    counts[3]++;
                    continue;
                }
            }

            std::cout << "0-60:\t" << counts[0] << std::endl;
            std::cout << "61-75:\t" << counts[1] << std::endl;
            std::cout << "76-90:\t" << counts[2] << std::endl;
            std::cout << "90-100:\t" << counts[3] << std::endl;
        }
        else if (command == "top")
        {
            size_t n;
            std::cout << "jumlah mahasiswa untuk ditampilkan: ";
            try
            {
                std::cin >> n;
                std::cin.ignore();
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
                std::cout << "Kesalahan input. n disetel menjadi 10";
                n = 10;
            }

            std::vector<std::string> allNim;
            // nimA, nimB, nimC, and nimD only need to be accessible in the following scope
            {
                std::vector<std::string> nimA = mkA->getCol(0);
                std::vector<std::string> nimB = mkB->getCol(0);
                std::vector<std::string> nimC = mkC->getCol(0);
                std::vector<std::string> nimD = mkD->getCol(0);
                allNim.insert(allNim.end(), nimA.begin(), nimA.end());
                allNim.insert(allNim.end(), nimB.begin(), nimB.end());
                allNim.insert(allNim.end(), nimC.begin(), nimC.end());
                allNim.insert(allNim.end(), nimD.begin(), nimD.end());
            }

            // only take unique NIMS across the files using unordered_set
            {
                std::unordered_set<std::string> allNimSet;
                for (size_t i = 0; i < allNim.size(); i++)
                    allNimSet.insert(allNim[i]);
                allNim.assign(allNimSet.begin(), allNimSet.end());
            }
            std::vector<StudentData *> studentDatas;
            for (std::string nim : allNim)
                studentDatas.push_back(getStudentData(nim));
            std::sort(studentDatas.begin(), studentDatas.end(),
                      [&](StudentData *a, StudentData *b) -> bool
                      {
                          return a->rerataNilai > b->rerataNilai;
                      });

            // finally, show it to 'em
            std::cout << "NIM\tNAMA RATA-RATA NILAI" << std::endl;
            for (size_t i = 0; i < n; i++)
            {
                std::cout << studentDatas[i]->nim << "\t";
                std::cout << studentDatas[i]->nama << " ";
                std::cout << studentDatas[i]->rerataNilai << std::endl;
            }

            for (StudentData *data : studentDatas)
                delete data;
        }
        else if (command == "help")
        {
            std::cout << manual << std::endl;
            std::cin.ignore();
        }
        else if (command == "quit")
            break;
        else
        {
            std::cout << "the command \"" << command << "\" is not recognized.\n"
                      << manual << std::endl;
            std::cin.ignore();
        }
        std::cout << "tekan Enter... ";
        std::cin.get();
    }

    return 0;
}

StudentData *getStudentData(std::string nim)
{
    StudentData *data = new StudentData;
    data->nim = nim;
    data->rerataNilai = 0;

    // data[0]: matkul-A; data[1]: matkul-B; dst.
    std::vector<std::vector<std::string>> datas;
    datas.push_back(mkA->getRow(nim, 0));
    datas.push_back(mkB->getRow(nim, 0));
    datas.push_back(mkC->getRow(nim, 0));
    datas.push_back(mkD->getRow(nim, 0));

    for (int i = 0; i < 4; i++)
    {
        if (datas[i].size() != 0)
        {
            // names are positioned at the second column in the csv files
            // this might execute multiple times, but still faster than ifs
            data->nama = datas[i][1];

            data->matkul.push_back(matkul[i]);
            // scores are positioned at the third column in the csv files
            data->nilai.push_back(std::stof(datas[i][2]));
            data->rerataNilai += data->nilai.back();
        }
    }
    data->rerataNilai /= data->nilai.size();

    return data;
}
