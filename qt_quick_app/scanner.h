#ifndef SCANNER_H
#define SCANNER_H

#include <QObject>
#include <QFutureWatcher>
#include "afm_object.h"
#include <QStateMachine>
#include "pid.h"
#include "dac.h"
#include "scan_data.h"

class Scanner : public AFMObject
{
    Q_OBJECT
    Q_PROPERTY(quint8 m_num_averages READ num_averages WRITE set_num_averages NOTIFY num_averages_changed)
    Q_PROPERTY(quint8 m_dwell_time READ dwell_time WRITE set_dwell_time NOTIFY dwell_time_changed)
    Q_PROPERTY(quint16 m_send_back_count READ send_back_count WRITE set_send_back_count NOTIFY send_back_count_changed)
    Q_PROPERTY(quint16 m_num_rows READ num_rows WRITE set_num_rows NOTIFY num_rows_changed)
    Q_PROPERTY(quint16 m_num_columns READ num_columns WRITE set_num_columns NOTIFY num_columns_changed)
    Q_PROPERTY(double m_rms_threshold READ rms_threshold WRITE set_rms_threshold NOTIFY rms_threshold_changed)
    Q_PROPERTY(int m_ratio READ ratio WRITE set_ratio NOTIFY ratio_changed)
    Q_PROPERTY(QString m_base_file_name READ base_file_name WRITE set_base_file_name NOTIFY base_file_name_changed)
    Q_PROPERTY(QChar m_leveling_direction READ leveling_direction WRITE set_leveling_direction NOTIFY leveling_direction_changed)

public:
    explicit Scanner(PID*, AFMObject* dac);
    void init();
    PID* pid;
    DAC* fine_z;

    Q_INVOKABLE quint8 num_averages();
    Q_INVOKABLE void set_num_averages(int num_averages);
    Q_INVOKABLE quint8 dwell_time();
    Q_INVOKABLE void set_dwell_time(int dwell_time);
    Q_INVOKABLE quint16 send_back_count();
    Q_INVOKABLE void set_send_back_count(int send_back_count);
    Q_INVOKABLE quint16 num_rows();
    Q_INVOKABLE void set_num_rows(int num_rows);
    Q_INVOKABLE quint16 num_columns();
    Q_INVOKABLE void set_num_columns(int num_columns);
    Q_INVOKABLE double rms_threshold();
    Q_INVOKABLE void set_rms_threshold(double rms_threshold);
    Q_INVOKABLE int ratio();
    Q_INVOKABLE void set_ratio(int ratio);
    Q_INVOKABLE QString base_file_name();
    Q_INVOKABLE void set_base_file_name(QString);
    Q_INVOKABLE QChar leveling_direction();
    Q_INVOKABLE void set_leveling_direction (QChar);

    void set_settings();
    void save_raw_data(QString save_folder);

signals:
    void scanner_initialization_done();
    void set_signal_generator_done();
    void all_data_received();
    void reset();
    void new_forward_offset_data(QString);
    void new_forward_phase_data(QString);
    void new_forward_error_data(QString);
    void new_reverse_offset_data(QString);
    void new_reverse_phase_data(QString);
    void new_reverse_error_data(QString);
    void started_scan_state_machine();

    // property changes
    void num_averages_changed(int);
    void dwell_time_changed(int);
    void send_back_count_changed(int);
    void num_rows_changed(int);
    void num_columns_changed(int);
    void rms_threshold_changed(double);
    void ratio_changed(int);
    void base_file_name_changed(QString);
    void leveling_direction_changed(QChar);
    void new_offset_line_profile(QVariantList);
    void new_phase_line_profile(QVariantList);
    void new_error_line_profile(QVariantList);


public slots:
    // Scan state machine methods
    void initialize_scan_state_machine();
    void set_signal_generator();
    void receive_data();
    void end_scan_state_machine();
    Q_INVOKABLE void start_state_machine();
    Q_INVOKABLE void pause_state_machine();
    Q_INVOKABLE void resume_state_machine();
    void cmd_step_scan();
    void handleFinished();
    void handleFinished_fo();
    void handleFinished_ro();
    void handleFinished_fp();
    void handleFinished_rp();
    void handleFinished_fe();
    void handleFinished_re();

private:
    QStateMachine m_state_machine;
    quint16 m_num_rows;
    quint16 m_num_columns;
    quint8 m_ratio;
    quint8 m_dwell_time;
    quint8 m_num_averages;
    quint16 m_send_back_count;
    double m_rms_threshold;
    QChar m_leveling_direction;

    int m_x_index;
    int m_y_index;
    
    void cmd_set_signal_generator();
    void cmd_start_scan();

    void cmd_set_dwell_time();
    void cmd_set_num_averages();
    void cmd_set_send_back_count();
    void cmd_set_leveling_direction();
    void callback_step_scan(QByteArray payload);
    void move_to_starting_point();
    bool is_scanning_forward();
    int get_delta_x_from_ratio();
    int get_delta_y_from_ratio();

    callback_return_type bind(void (Scanner::*method)(QByteArray));
    typedef void (Scanner::*callback_type)(QByteArray);
    bool scanning_forward;
    bool m_should_pause;
    QString m_base_file_name;

    ScanData* fwd_offset_data;
    ScanData* fwd_phase_data;
    ScanData* fwd_error_data;
    ScanData* rev_offset_data;
    ScanData* rev_phase_data;
    ScanData* rev_error_data;

    QFutureWatcher<QString> watcher_fo;
    QFutureWatcher<QString> watcher_ro;
    QFutureWatcher<QString> watcher_fp;
    QFutureWatcher<QString> watcher_rp;
    QFutureWatcher<QString> watcher_fe;
    QFutureWatcher<QString> watcher_re;

    QVariantList get_latest_line_profile(ScanData* fwd, ScanData* rev);

    static const QString settings_group_name;
};

#endif // SCANNER_H
