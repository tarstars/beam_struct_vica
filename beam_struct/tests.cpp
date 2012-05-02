/*void test_tensor(){
    Tensor t = make_material_tensor(5.6e10, 5.145e10, 2.2e10, 10.6e10, 6.6e10, 2.65e10);
    Vector3 n(0,0,1);
    n.normalize();
    get_log() << t << endl;
    t.make_cristoffel(n);
}

void test_vector() {
    Vector3 a(1, 2, 3), b(1, 2, 4);
    cout<< "a=" << a << " b="<< b << endl;
    cout << "a+b=" << a+b << endl;
    Vector3 norm(3,4,5);
    cout<<norm<<endl;
    norm.normalize();
    cout<<norm;
}

void test_polinom_order(){
    Tensor tt = make_material_tensor (5.6e10, 5.145e10, 2.2e10, 10.6e10, 6.6e10, 2.65e10);
    Tensor t=tt.rotation_for_VB_picture(9.0/180*M_PI);

    double rho=5.96e3;

    PolyMatrix p_1=t.make_polyMatrix(rho, 0, 0);
    Polinom d;

    d=p_1.Determinant();

    vector<CD> f_1;

    f_1=d.all_roots();

    cout<<"  "<<f_1<<endl<<endl;

    Vector3 n(cos(9*2*M_PI/360)/sqrt(2), cos(9*2*M_PI/360)/sqrt(2), -sin(9*2*M_PI/360));
    cout<<"vector"<<n<<endl<<endl;
    Matrix3 p_2;
    p_2=tt.make_cristoffel(n);
    d=p_2.char_poly();
    cout<<d<<endl;
    vector <CD> f_2;
    f_2=d.all_roots();
    for (int i=0; i<3; i++){
        CD p=sqrt(rho/f_2[i]);
        f_2[i]=p;
    };
    cout<<"  "<<f_2;


};


void test_matrix(){

    Matrix3 a;
    a(0,0)=1;
    a(0,1)=1;
    a(0,2)=1;
    a(1,0)=1;
    a(1,1)=2;
    a(1,2)=4;
    a(2,0)=1;
    a(2,2)=9;
    a(2,1)=3;

}

void test_vector1(){
    Tensor t = make_material_tensor (5.6e10, 5.145e10, 2.2e10, 10.6e10, 6.6e10, 2.65e10);
   PolyMatrix p;
    double rho=5.96e3;
    p= t.make_polyMatrix(rho,0.00,0.00);
    Polinom d;
    d=p.Determinant();
    vector<CD> f;
    f=d.all_roots();
    vector <double> freal;
    vector <CD> fimage;
    freal=real_part(f);
    fimage=image_part(f);
    cout<<f<<endl<<freal<<fimage;

    //cout<<"  "<<f<<endl;
   // cout<<f;


}

QImage mapa_for_roots(){
   // ofstream dest("a.txt");
    int n=200;
    matrix mat(n,n);
    Tensor t = make_material_tensor (5.6e10, 5.145e10, 2.2e10, 10.6e10, 6.6e10, 2.65e10);
    PolyMatrix p;
    double rho=5.96e3;
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            double s_1=-0.002+(0.004/n)*i;
            double s_2=-0.002+(0.004/n)*j;
            p= t.make_polyMatrix(rho,s_1,s_2);
            Polinom d;
            d=p.Determinant();
            vector<CD> f;
            f=d.all_roots();
            vector <double> freal;
            vector <CD> fimage;
            freal=real_part(f);
            fimage=image_part(f);
            mat(i,j)=freal.size();

        }

    }
    QImage mapa(n,n,QImage::Format_ARGB32_Premultiplied);
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            int val=mat(i,j);
            if (val==2)
            {mapa.setPixel(i,j,qRgb(2,2,255));}
            if (val==4)
            {mapa.setPixel(i,j,qRgb(2,255,2));}
            if (val==6)
            {mapa.setPixel(i,j,qRgb(200,2,2));}
            if((val!=6)&&(val!=4)&&(val!=2))  {mapa.setPixel(i,j,qRgb(100,200,200));}


            }}
    mapa.save("Mapa.png");
    return mapa;
 }

 bool comp(const CD& a,const CD& b){
   return real(a)<real(b);
 }

 void povorot(){
     ofstream dest("a_povorot.txt");
     Tensor tt = make_material_tensor (5.6e10, 5.145e10, 2.2e10, 10.6e10, 6.6e10, 2.65e10);
     Tensor t=tt.rotation(10.0/180*M_PI,'z');
    // int n=100;
     int m=1000;
         double rho=5.96e3;
         for (double phi=0; phi<(2*M_PI); phi+=(2*M_PI)/500){
             cout<<phi;
             double s_1=cos(phi);
             double s_2=sin(phi);
             Vector3 n(s_1, s_2, 0);
             Matrix3 p;
             p=t.make_cristoffel(n);
             Polinom d=p.char_poly();
             vector<CD> f;
             f=d.all_roots();
             vector <double> freal;
             freal=real_part(f);
             sort(freal.begin(),freal.end());

             //cout << "\ts1 = " << s_1 << " gamma = " << freal[0] << endl;

             dest<<"sphere{<"<<s_1*sqrt(rho*freal[2])*m<<", 0, "<<s_2*sqrt(rho*freal[2])*m<<">, 0.02 pigment {color<1, 1, 1>}}"<<endl;}
 }


 void testPol(){
 Vector3 a(0, 0, 1);
 Vector3 b(1/sqrt(2), 1/sqrt(2), 0);
 Vector3 c(0.5, 0.5, 1/sqrt(2));

 Matrix3 Matr(a,b,c);
 Matrix3 Matrr(b,c,a);
 cout<<Matr.calc_pol()<<endl<<endl;
 cout<<Matrr.calc_pol()<<endl<<endl;
 }*/
