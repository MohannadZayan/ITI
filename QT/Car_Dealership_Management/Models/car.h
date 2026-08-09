#ifndef CAR_H
#define CAR_H
#include <QString>

// ? This is an enum class, Reserves only a certain set of values for the car status variable.
enum class CarStatus {
    Available,
    Reserved,
    Sold,
    InTransit
};
enum class TransmissionType {
    Manual,
    Automatic,
    CVT,
    DualClutch
};
// * Represents a single vehicle in the dealirship inventory.
class Car
{
    // * Private fields
    private:

    int m_id;

    QString m_make;
    QString m_model;

    int m_year;

    double m_price;
    int m_mileage;

    QString m_color;

    QString m_engineName;
    int m_horsepower;

    TransmissionType m_transmission;

    bool m_isNew;

    QString m_licensePlate;
    QString m_vin;

    CarStatus m_status;
 //* Public fields
public:
// * Default constructor and destructor
    Car();

    ~Car() = default;

    Car (

        const QString& make,
        const QString& model,
        int year,
        double price,
        int mileage,
        const QString& color,
        const QString& engineName,
        int horsepower,
        const TransmissionType transmission,
        bool isNew,
        const QString& licensePlate,
        const QString& vin,
        CarStatus status
    );

    // *Getters
    // ? The first const returns a reference to a constant string, the second const indicates that the method does not modify the object.

    int id() const;
    const QString& make() const;
    const QString& model() const;
    int year() const;
    double price() const;
    int mileage() const;
    const QString& color() const;
    const QString& engineName() const;
    int horsepower() const;
    TransmissionType transmission() const;
    bool isNew() const;
    const QString& licensePlate() const;
    const QString& vin() const;
    CarStatus status() const;

    // *Setters
          //? You might ask "boolean setters?" Yes, it's for the input validation and might be used in upcoming classes.
    bool setPrice (double price);
    bool setMileage (int mileage);
    void setStatus (CarStatus status);
    void setLicensePlate (const QString &licensePlate);
    
};

#endif // CAR_H
