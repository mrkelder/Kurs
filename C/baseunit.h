//������ ��������� �������
//-----------------------��������� ������� ������ 
//����� ��������� �� ����� � �������� ������� �������
void wait_press_key(char *msg);
//����� ������ S �� �����, � � ����
void WritelnString(char S[80]);
// ���������� ������ S �� ����� len ���������  
char *FillString(char *S, unsigned char len, unsigned char pk);
// ���� ����� � ���������� � ���������; 
double GetNumber(double MinNumber, double MaxNumber, 
									char m1,char n1,char m2,char n2);
//������ �� ���������� ��� ������ ����������� 
void UsesDevice();
//�������� ����� � ������� ������������ Kodifs
int SearchKodif(char* Kod, int nk);
//���������� ������������ �� ����������� ���� ��������
void SortKodif(int nk);
//������ ���� �������. �������� � ����� ������� 
void ReversProduct(DynProduct **Lp);
//������ ��������� ����� ������ � ������������ ���� �������� 
int ReadFileOut(int *np, DynProduct **Lp);
//�������� ���� �������
void DisposeProduct(DynProduct *Lp);
//������ �������� �� ���� � �������� ���� ������
int WriteFileOut(DynProduct *Lp);
