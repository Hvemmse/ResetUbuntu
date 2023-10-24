#include <gtk/gtk.h>
#include <iostream>
#include <cstdlib>

// Funktion til at udføre systemkommandoer
int executeCommand(const char* command) {
    return system(command);
}

// Funktion, der udføres, når backup-knappen klikkes
static void on_backup_button_clicked(GtkWidget *widget, gpointer data) {
    // Udfør backupkommando
    int result = executeCommand("dconf dump / > gnome-settings-backup.dconf");
    
    if (result == 0) {
        std::cout << "Indstillinger er blevet sikkerhedskopieret i 'gnome-settings-backup.dconf'" << std::endl;
    } else {
        std::cerr << "Fejl under backup." << std::endl;
    }
}

// Funktion, der udføres, når nulstil-knappen klikkes
static void on_reset_button_clicked(GtkWidget *widget, gpointer data) {
    // Udfør nulstillingskommando
    int result = executeCommand("dconf reset -f /");

    if (result == 0) {
        std::cout << "Indstillinger er blevet nulstillet." << std::endl;
    } else {
        std::cerr << "Fejl under nulstilling." << std::endl;
    }
}

// Funktion, der udføres, når gendan-knappen klikkes
static void on_restore_button_clicked(GtkWidget *widget, gpointer data) {
    // Udfør gendannelseskommando
    int result = executeCommand("dconf load / < gnome-settings-backup.dconf");

    if (result == 0) {
        std::cout << "Indstillinger er blevet gendannet fra backupfilen." << std::endl;
    } else {
        std::cerr << "Fejl under gendannelse." << std::endl;
    }
}

// Funktion til at vise About-vinduet
static void show_about_dialog(GtkWidget *widget, gpointer data) {
    GtkWidget *about_dialog = gtk_message_dialog_new(
        NULL,
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "Programmet er for at nulstille din gnome indstillinger:\nResetGnome\n\nForfatter:\nFrank Simens\n\nEmail: frank@simens.dk\n\nInternetadresse: https://www.112support.dk"
    );

    gtk_window_set_title(GTK_WINDOW(about_dialog), "Om Programmet");
    gtk_dialog_run(GTK_DIALOG(about_dialog));
    gtk_widget_destroy(about_dialog);
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *backup_button;
    GtkWidget *reset_button;
    GtkWidget *restore_button;
    GtkWidget *about_button;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GNOME Backup og Nulstilling");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    backup_button = gtk_button_new_with_label("Backup Indstillinger");
    reset_button = gtk_button_new_with_label("Nulstil Indstillinger");
    restore_button = gtk_button_new_with_label("Gendan Indstillinger fra Backup");
    about_button = gtk_button_new_with_label("Om Programmet");

    g_signal_connect(backup_button, "clicked", G_CALLBACK(on_backup_button_clicked), NULL);
    g_signal_connect(reset_button, "clicked", G_CALLBACK(on_reset_button_clicked), NULL);
    g_signal_connect(restore_button, "clicked", G_CALLBACK(on_restore_button_clicked), NULL);
    g_signal_connect(about_button, "clicked", G_CALLBACK(show_about_dialog), NULL);

    gtk_box_pack_start(GTK_BOX(box), backup_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), reset_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), restore_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), about_button, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), box);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}

// Kompilerings info 
// g++ -o resetubuntuuk resetubuntuuk.cpp `pkg-config --cflags --libs gtk+-3.0`
