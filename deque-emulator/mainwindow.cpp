#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include "algo.h"

constexpr size_t MAX_DEQUE_SIZE = 1000;
constexpr size_t MIN_DEQUE_SIZE = 0;

static std::deque<std::string> tea {
    "Чай Лунцзин",
    "Эрл Грей",
    "Сенча",
    "Пуэр",
    "Дарджилинг",
    "Ассам",
    "Матча",
    "Ганпаудер",
    "Оолонг",
    "Лапсанг Сушонг"
};

static std::deque<std::string> cakes {
    "Красный бархат",
    "Наполеон",
    "Медовик",
    "Тирамису",
    "Прага",
    "Чизкейк",
    "Захер",
    "Эстерхази",
    "Морковный торт",
    "Чёрный лес",
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
      , random_gen_(std::random_device{}()) {
    ui->setupUi(this);
    ApplyModel();
    ApplyIterator();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::ApplyModel() {
    QStringList elements;
    for(size_t i = 0; i < deque_model_.items.size(); ++i) {
        elements << QString::fromStdString(std::to_string(i) + ": " + deque_model_.items[i]);
    }
    elements << "end";
    auto preserve_iter = deque_model_.iterator;

    ui->list_widget->clear();
    ui->list_widget->addItems(elements);

    ui->txt_size->setText(QString::number(deque_model_.items.size()));
    ui->pb_pop_back->setDisabled(deque_model_.items.empty());
    ui->pb_pop_front->setDisabled(deque_model_.items.empty());

    deque_model_.iterator = preserve_iter;
    ApplyIterator();
}

void MainWindow::ApplyIterator() {
    bool disabled = deque_model_.iterator == deque_model_.items.end();
    auto position = deque_model_.iterator - deque_model_.items.begin();
    ui->list_widget->setCurrentRow(position);
    ui->pb_edit->setDisabled(disabled);
    ui->pb_erase->setDisabled(disabled);
    if (!disabled) {
        ui->txt_elem_content->setText(QString::fromStdString(*deque_model_.iterator));
    } else {
        ui->txt_elem_content->setText("");
    }
    ui->pb_dec->setDisabled(deque_model_.iterator == deque_model_.items.begin());
    ui->pb_inc->setDisabled(disabled);
}

void MainWindow::SetRandomGen(const std::mt19937 &random_gen) {
    random_gen_ = random_gen;
}

void MainWindow::on_pb_pop_back_clicked() {
    deque_model_.items.pop_back();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_pb_push_back_clicked() {
    deque_model_.items.push_back(ui->txt_elem_content->text().toStdString());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_pb_clear_clicked() {
    deque_model_.items.clear();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_pb_preset_tea_clicked() {
    deque_model_.items = tea;
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_pb_preset_cakes_clicked() {
    deque_model_.items = cakes;
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_list_widget_currentRowChanged(int currentRow) {
    currentRow = std::clamp(currentRow, 0, (int)deque_model_.items.size());
    deque_model_.iterator = deque_model_.items.begin() + currentRow;
    ApplyIterator();
}

void MainWindow::on_pb_erase_clicked() {
    deque_model_.items.erase(deque_model_.iterator);
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_pb_insert_clicked() {
    deque_model_.items.insert(deque_model_.iterator,ui->txt_elem_content->text().toStdString());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_pb_inc_clicked() {
    deque_model_.iterator = std::next(deque_model_.iterator);
    ApplyModel();
}

void MainWindow::on_pb_dec_clicked() {
    deque_model_.iterator = std::prev(deque_model_.iterator);
    ApplyModel();
}

void MainWindow::on_pb_begin_clicked() {
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_pb_end_clicked() {
    deque_model_.iterator = deque_model_.items.end();
    ApplyModel();
}

void MainWindow::on_pb_edit_clicked() {
    *deque_model_.iterator = ui->txt_elem_content->text().toStdString();
    ApplyModel();
}

void MainWindow::on_pb_resize_clicked() {
    bool correct;
    size_t new_size = ui->txt_size->text().toInt(&correct);
    if (!correct || new_size > MAX_DEQUE_SIZE || new_size < MIN_DEQUE_SIZE) {
        ui->txt_size->setText(QString::number(deque_model_.items.size()));
        return;
    }
    deque_model_.items.resize((new_size));
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();

}

void MainWindow::on_pb_find_clicked() {
    deque_model_.iterator = std::find(deque_model_.items.begin(),deque_model_.items.end(),ui->txt_elem_content->text().toStdString());
    ApplyIterator();
}

void MainWindow::on_pb_count_clicked() {
    ui->lbl_count->setText(QString::number(std::count(deque_model_.items.begin(),deque_model_.items.end(),ui->le_count->text().toStdString())));
}

void MainWindow::on_pb_min_element_clicked() {
    deque_model_.iterator = std::min_element(deque_model_.items.begin(),deque_model_.items.end());
    ApplyIterator();
}

void MainWindow::on_pb_max_element_clicked() {
    deque_model_.iterator = std::max_element(deque_model_.items.begin(),deque_model_.items.end());
    ApplyIterator();
}

void MainWindow::on_pb_sort_clicked() {
    deque_model_.items = MergeSort(deque_model_.items,std::less<std::string>());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_pb_sort_any_clicked() {
    deque_model_.items = MergeSort(deque_model_.items, [](const std::string& a, const std::string& b){
        return QString::compare(QString::fromStdString(a),QString::fromStdString(b),Qt::CaseInsensitive) < 0;
    });
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_pb_unique_clicked() {
    if (!std::is_sorted(deque_model_.items.begin(),deque_model_.items.end())) {
            return;
        }
    auto to_del_iter = std::unique(deque_model_.items.begin(),deque_model_.items.end());
    deque_model_.items.erase(to_del_iter,deque_model_.items.end());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_pb_reverse_clicked() {
    std::reverse(deque_model_.items.begin(),deque_model_.items.end());
    ApplyModel();
}

void MainWindow::on_pb_shuffle_clicked() {
    std::shuffle(deque_model_.items.begin(),deque_model_.items.end(),random_gen_);
    ApplyModel();
}

void MainWindow::on_pb_pop_front_clicked() {
    deque_model_.items.pop_front();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_pb_push_front_clicked() {
    deque_model_.items.push_front(ui->txt_elem_content->text().toStdString());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_pb_lower_bound_clicked() {
    if (!std::is_sorted(deque_model_.items.begin(),deque_model_.items.end())) {
        return;
    }
    deque_model_.iterator = std::lower_bound(deque_model_.items.begin(),deque_model_.items.end(),ui->txt_elem_content->text().toStdString());
    ApplyModel();
}

void MainWindow::on_pb_upper_bound_clicked() {
    if (!std::is_sorted(deque_model_.items.begin(),deque_model_.items.end())) {
        return;
    }
    deque_model_.iterator = std::upper_bound(deque_model_.items.begin(),deque_model_.items.end(),ui->txt_elem_content->text().toStdString());
    ApplyModel();
}
