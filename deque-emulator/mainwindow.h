#pragma once

#include <QMainWindow>
#include <QStringListModel>
#include <QListWidgetItem>
#include <random>

#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
    }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   void SetRandomGen(const std::mt19937& random_gen);

private slots:

    void on_pb_pop_back_clicked();

    void on_pb_push_back_clicked();

    void on_pb_clear_clicked();

    void on_pb_preset_tea_clicked();

    void on_pb_preset_cakes_clicked();

    void on_list_widget_currentRowChanged(int currentRow);

    void on_pb_erase_clicked();

    void on_pb_insert_clicked();

    void on_pb_inc_clicked();

    void on_pb_dec_clicked();

    void on_pb_begin_clicked();

    void on_pb_end_clicked();

    void on_pb_edit_clicked();

    void on_pb_resize_clicked();

    void on_pb_find_clicked();

    void on_pb_count_clicked();

    void on_pb_min_element_clicked();

    void on_pb_max_element_clicked();

    void on_pb_sort_clicked();

    void on_pb_sort_any_clicked();

    void on_pb_unique_clicked();

    void on_pb_reverse_clicked();

    void on_pb_shuffle_clicked();

    void on_pb_pop_front_clicked();

    void on_pb_push_front_clicked();

    void on_pb_lower_bound_clicked();

    void on_pb_upper_bound_clicked();

private:

    void ApplyModel();

    void ApplyIterator();

private:
    Model deque_model_;
    Ui::MainWindow *ui;
    std::mt19937 random_gen_;
};


